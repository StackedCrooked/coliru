// an inline declaration

    template <typename Fx, typename T0, typename T1>
	Thread::Thread( Fx&& fx, T0&& arg0, T1&& arg1 ) : 
		threadjump( std::bind( std::forward( fx ), std::forward( arg0 ), std::forward( arg1 ) ) ), 
		done( false ), 
		thread( [&](){ threadjump(); done = true; } ) {

	}