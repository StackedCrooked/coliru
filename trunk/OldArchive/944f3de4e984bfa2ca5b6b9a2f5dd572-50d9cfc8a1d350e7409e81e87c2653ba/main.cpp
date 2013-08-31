/*template <typename TFx, typename... Tn> 
auto Queue ( TFx&& fx, Tn&&... args ) -> std::future< decltype( fx(args...) ) > {
	typedef decltype( fx(args...) ) TResult;

	return Queue( std::is_void<TResult>(), 
		std::forward<TFx>( fx ), 
		std::forward<Tn>( args )... );
}*/

template <typename TFx, typename T0> 
auto Queue ( TFx&& fx, T0&& arg0 ) -> std::future< decltype( fx( arg0 ) ) > {
	typedef decltype( fx( arg0 ) ) TResult;
	return Queue( std::is_void<TResult>(), 
		std::forward<TFx>( fx ), 
		std::forward<T0>( arg0 ) );
}

template <typename TFx, typename T0> 
auto Queue ( std::true_type t, TFx&& fx, T0&& arg0 ) -> std::future< decltype( fx( arg0 ) ) > {
    typedef decltype( fx( arg0 ) ) TResult;
	typedef std::future< TResult > TFuture;
	typedef std::promise< TResult > TPromise;

	std::shared_ptr<TPromise> promise = make_shared<TPromise>( );

	std::function<void()> workitem = [=]( ){ 
		std::function<TResult()> f = std::bind( fx, arg0 );
		try {
			f();
		}
		catch ( ... ) {
			promise->set_exception( std::current_exception() );
		}
	};

	QueueWork( work );

	return promise->get_future();
}

template <typename TFx, typename T0> 
auto Queue ( std::false_type t, TFx&& fx, T0&& arg0 ) -> std::future< decltype( fx( arg0 ) ) > {
    typedef decltype( fx( arg0 ) ) TResult;
	typedef std::future< TResult > TFuture;
	typedef std::promise< TResult > TPromise;

	std::shared_ptr<TPromise> promise = std::make_shared<TPromise>( );

	std::function<void()> workitem = [=]( ){ 
		std::function<TResult()> f = std::bind( fx, arg0 );
		try {
			// Force any result from f to be moved ( if possible )
			// ( Will the compiler do this automatically? )
			promise->set_value( std::move( f() ) );
		}
		catch ( ... ) {
			promise->set_exception( std::current_exception() );
		}
	};

	QueueWork( std::move( workitem ) );

	return promise->get_future();
}

/*template <typename TFx, typename ...Tn> 
auto Queue ( std::false_type t, TFx&& fx, Tn&&... argn ) -> std::future< decltype( fx( argn... ) ) > {
	typedef decltype( fx( argn... ) ) TResult;
	typedef std::future< TResult > TFuture;
	typedef std::promise< TResult > TPromise;

	std::shared_ptr<TPromise> promise = std::make_shared<TPromise>( );

	std::function<void()> workitem = [=]( ){ 
		std::function<TResult()> f = std::bind( fx, argn... );
		try {
			// Force any result from f to be moved ( if possible )
			// ( Will the compiler do this automatically? )
			promise->set_value( std::move( f() ) );
		}
		catch ( ... ) {
			promise->set_exception( std::current_exception() );
		}
	};

	QueueWork( std::move( workitem ) );

	return promise->get_future();
}

template <typename TFx, typename ...Tn> 
auto Queue ( std::true_type t, TFx&& fx, Tn&&... argn ) -> std::future< decltype( fx( argn... ) ) > {
	typedef decltype( fx( argn... ) ) TResult;
	typedef std::future< TResult > TFuture;
	typedef std::promise< TResult > TPromise;

	std::shared_ptr<TPromise> promise = make_shared<TPromise>( );

	std::function<void()> workitem = [=]( ){ 
		std::function<TResult()> f = std::bind( fx, argn... );
		try {
			f();
		}
		catch ( ... ) {
			promise->set_exception( std::current_exception() );
		}
	};

	QueueWork( work );

	return promise->get_future();
}*/