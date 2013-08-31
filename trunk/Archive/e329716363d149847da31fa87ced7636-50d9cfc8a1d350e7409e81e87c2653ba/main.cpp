#ifndef FURROVINELOG_H
#define FURROVINELOG_H

#include <Furrovine++/Std.h>
#include <Furrovine++/Collections/Concurrent/BlockingQueue.h>
#include <Furrovine++/Threading/Thread.h>
#include <Furrovine++/Threading/ThreadStopException.h>
#include <Furrovine++/Diagnostics/LogLevel.h>

namespace Furrovine { namespace Diagnostics {

    class Log {
	private:
		typedef std::function<void()> TWork;
		Collections::Concurrent::BlockingQueue<TWork> work;
		Threading::Thread logthread;
		std::stringstream buffer;
		std::ostream& sink;
		std::atomic<LogLevel> verbosity;

		template <typename T>
		void FormattedWrite ( LogLevel level, T&& object, std::chrono::system_clock::time_point time ) {
			if ( level < verbosity )
				return;
			switch ( level ) {
			case LogLevel::LOL:
				buffer << "[ LOL ] ";
				break;
			case LogLevel::FTR:
				buffer << "[ FTR ] ";
				break;
			case LogLevel::FYI:
				buffer << "[ FYI ] ";
				break;
			case LogLevel::WTF:
				buffer << "[ WTF ] ";
				break;
			case LogLevel::OMG:
				buffer << "[ OMG ] ";
				break;
			case LogLevel::FML:
				buffer << "[ FML ] ";
				break;
			}
			buffer << "( ";
			buffer << std::put_time( std::localtime( &time ), "%T, %F" );
			buffer << " ) ";
			buffer << object;
			buffer << '\n';
		}

		void RunThread () {
			while ( true ) {
				try {
					TWork workitem;
					if ( work.Pop( workitem ) ) {
						workitem( );
					}
				}
				catch ( const Threading::ThreadStopException& ex ) {
					buffer << "Logging Thread is Stopping ... " << ex.What() << std::endl;
					break;
				}
			}
			buffer << "Logging Thread is Terminating ... " << std::endl;
		}

		void Sink () {
			sink << buffer;
		}

		void Flush () {
			sink << buffer << std::endl;
		}

		void Stop () {
			throw Threading::ThreadStopException();
		}

	public:

		Log ( std::ostream& outputstream, LogLevel initialverbosity ) 
		: sink( outputstream ), verbosity( initialverbosity ) {
			logthread.Reset( &Log::RunThread, this );
		}

		template <typename T>
		void Write ( T&& object, LogLevel level = LogLevel::FYI ) {
			TWork workitem = std::bind( &Log::FormattedWrite, this, level, std::forward<T>( object ), std::chrono::system_clock::now() );
			work.Push( work );
		}

		~Log () {
			TWork sinkworkitem = std::bind( &Log::Sink, this );
			TWork stopworkitem = std::bind( &Log::Stop, this );
			work.Push( sinkworkitem );
			work.Push( stopworkitem );
			logthread.Join();
			Flush();
		}
	};

}}

#endif // FURROVINELOG_H 