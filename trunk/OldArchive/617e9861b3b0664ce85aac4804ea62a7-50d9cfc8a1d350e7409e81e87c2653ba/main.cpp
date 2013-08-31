#ifndef FURROVINETHREADPOOL_H
#define FURROVINETHREADPOOL_H

#include <Furrovine++/Threading/Thread.h>
#include <Furrovine++/Collections/Concurrent/BlockingQueue.h>

namespace Furrovine { namespace Threading {

    class ThreadPool {
	private:
		typedef int TCost;
		typedef ulword TIndex;
		typedef std::pair<TIndex, TCost> TThreadCost;
		typedef std::function<void()> TWork;
		typedef Collections::Concurrent::BlockingQueue<TWork> TQueue;

		struct Cost {
			bool operator () ( const TThreadCost& left, const TThreadCost& right ) {
				return left.second > right.second;
			}
		};

		std::vector<TWork> work;
		std::vector<Thread> threads;
		std::vector<ptr<TQueue>> threadwork;
		std::priority_queue<TThreadCost, std::vector<TThreadCost>, Cost> threadpriorities;

		ThreadPool ( const ThreadPool& nocopy ) {

		}

		ThreadPool& operator= ( const ThreadPool& nocopy ) {
			return *this;
		}

	public:

		ThreadPool () {
			ulword startcount = std::thread::hardware_concurrency();
			for ( ulword i = 0; i < startcount; ++i ) {
				threadwork.emplace_back( new TQueue() );
				threadpriorities.emplace( TThreadCost( i, 0 ) );
				threads.emplace_back( 
					[ this, i ]( ){ 
						while ( true ) {
							try {
								TWork work = this->threadwork[ i ]->Pop();
								work( );
							}
							catch ( QuitException& quit ) {
								std::cout << "Thread is Quitting" << std::endl;
							}
							catch ( ... ) {
								std::cout << "WHAT THE SHIT THREADPOOL EXPLOSION!" << std::endl;
							}
						} 
					}
				);
			}
		}

		template <typename TFx, typename... Tn> 
		std::future< typename std::result_of<TFx( Tn... )>::type > 
		Queue ( TFx&& fx, Tn&&... argn ) {
			typedef decltype( fx( argn... ) ) TResult;
			typedef std::future<TResult> TFuture;
			typedef std::promise<TResult> TPromise;
			std::shared_ptr<TPromise> promise = std::make_shared<TPromise>( );

			QueueWork( MakeWork<TResult>( promise, std::bind( std::forward<TFx>( fx ), std::forward<Tn>( argn )... ) ) );

			return promise->get_future();
		}

		~ThreadPool ( ) {
			
		}

	private:

		template <typename TResult, typename T>
		TWork MakeWork ( std::shared_ptr<std::promise<TResult>> promise, T&& binding ) {
			return MakeWork<TResult, T>( std::is_void<TResult>(), promise, std::forward<T>( binding ) );
		}

		template <typename TResult, typename T>
		TWork MakeWork ( std::false_type f, std::shared_ptr<std::promise<TResult>> promise, T&& binding ) {
			
			return TWork(
			[=]( ){ 
				std::function<TResult()> f = binding;
				try {
					// Force any result from f to be moved ( if possible )
					// ( Will the compiler do this automatically? )
					promise->set_value( std::move( f() ) );
				}
				catch ( ... ) {
					promise->set_exception( std::current_exception() );
				}
			} );
		}

		template <typename TResult, typename T>
		TWork MakeWork ( std::true_type t, std::shared_ptr<std::promise<TResult>> promise, T&& binding ) {
			return TWork( 
			[=]( ){ 
				std::function<TResult()> f = binding;
				try {
					f();
				}
				catch ( ... ) {
					promise->set_exception( std::current_exception() );
				}
			} );
		}

		void QueueWork ( TWork item ) {
			if ( !threadpriorities.empty() ) {
				TThreadCost threadcost = threadpriorities.top();
				TQueue& threadworkqueue = *threadwork[ threadcost.first ];
				threadpriorities.pop();
				
				++threadcost.second;
				threadworkqueue.Push( std::move( item ) );
				threadpriorities.push( std::move( threadcost ) );
			}
			else {
				// Save it for later
				// for the threads 
				// to pick up afterwards
				work.emplace_back(
					std::move( item )
				);
			}
		}

	};

}}

#endif // FURROVINETHREADPOOL_H 