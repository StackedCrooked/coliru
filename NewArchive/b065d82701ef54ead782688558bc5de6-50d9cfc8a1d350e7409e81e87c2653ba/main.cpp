class Dispatcher {
    protected:
		typedef std::unique_ptr<DispatchBase> TDispatch;
		typedef std::vector<TDispatch> TDispatchList;
		typedef std::lock_guard<std::mutex> TLockGuard;
		TDispatchList work;
		std::mutex thislock;
		std::thread::id threadid;

	public:
		Dispatcher () : threadid ( std::this_thread::get_id() ) {

		}

		template <typename R> 
		void Add ( std::function<R ( )>&& f ) {
			TLockGuard guard( thislock );
			work.emplace_back( TDispatch( new Dispatch0<R>(
				std::forward<std::function<R ()>&&>( f ) ) ) );
		}

		template <typename R, typename T1> 
		void Add ( std::function<R (T1)>&& f, T1&& t1  ) {
			TLockGuard guard( thislock );
			work.emplace_back( TDispatch( new Dispatch1<R, T1>( 
				std::forward<std::function<R (T1)>&&>( f ), 
				std::forward<T1>( t1 ) ) ) );
		}

		template <typename R, typename T1, typename T2> 
		void Add ( std::function<R (T1, T2)>&& f, T1&& t1, T2&& t2 ) {
			TLockGuard guard( thislock );
			work.emplace_back( 
				TDispatch( new Dispatch2<R, T1, T2>(
				std::forward<std::function<R (T1, T2)>&&>( f ), 
				std::forward<T1>( t1 ), 
				std::forward<T2>( t2 ) ) ) );
		}

		template <typename R, typename T1, typename T2, typename T3> 
		void Add ( std::function<R (T1, T2, T3)>&& f, T1&& t1, T2&& t2, T3&& t3 ) {
			TLockGuard guard( thislock );
			work.emplace_back( TDispatch( 
				new Dispatch3<R, T1, T2, T3>( f, 
				std::forward<T1>( t1 ), 
				std::forward<T2>( t2 ), 
				std::forward<T3>( t3 ) ) ) );
		}

		template <typename R, typename T1, typename T2, typename T3, typename T4> 
		void Add ( std::function<R (T1, T2, T3, T4)>&& f, T1&& t1, T2&& t2, T3&& t3, T4&& t4 ) {
			TLockGuard guard( thislock );
			work.emplace_back( TDispatch( 
				new Dispatch4<R, T1, T2, T3, T4>( 
				std::forward<std::function<R (T1, T2, T3, T4)>&&>( f ), 
				std::forward<T1>( t1 ), 
				std::forward<T2>( t2 ), 
				std::forward<T3>( t3 ), 
				std::forward<T4>( t4 ) ) ) );
		}

		void Invoke () {
			TDispatchList dispatchwork; {
				TLockGuard guard(thislock);
				dispatchwork = std::move( work );
			}

			for ( auto&& task : dispatchwork ) {
				(*task)( );
			}
		}

		void operator() () {
			Invoke();
		}
	};