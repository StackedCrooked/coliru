ThreadPool () {
	ulword startcount = std::thread::hardware_concurrency();
	//threadwork.reserve( startcount );
	//threads.reserve( startcount );
	for ( ulword i = 0; i < startcount; ++i ) {
		threadwork.emplace_back( );
		threadpriorities.emplace( TThreadCost( i, 0 ) );
		threads.emplace_back( 
			[]( ThreadPool& pool, ulword i ){ 
				ulword index = i;
				while ( true ) {
					try {
						TWork work = pool.threadwork[ index ].Pop();
						work( );
					}
					catch ( ... ) {
						std::cout << "WHAT THE SHIT THREADPOOL EXPLOSION!" << std::endl;
					}
				} 
			},
			std::ref( *this ), i
		);
	}
}