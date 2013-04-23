template <typename TFx, typename... TArgs> 
std::future< decltype( fx(args...) ) > Queue ( TFx&& fx, TArgs&&... args ) {
	typedef decltype( fx(args...) ) TResult;
	std::promise<TResult> promise;
	std::function<void()> work( 
		[&]( ){ 
			auto f = std::bind( std::forward( fx ), std::forward( args )... );
			try {
				// Force any result from f to be moved ( if possible )
				// ( Will the compiler do this automatically? )
				promise.set_value( std::move( f() ) );
			}
			catch ( ... ) {
				promise.set_exception( std::current_exception() );
			}
		};
	);
	threadwork.emplace_back(
		std::move( work );
	);
}