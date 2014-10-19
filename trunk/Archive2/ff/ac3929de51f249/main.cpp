#include <string>
#include <iostream>
#include <stack>
#include <ctime>

int main( int argc, char* argv[] )
{
    if( argc == 2 )
    {
        try
        {
            const std::size_t N = std::stoi( argv[1] ) ;
            
            {
                const auto n = std::clock() ;
                while( n == std::clock() ) ;
                std::cout << "N == " << N << "  true resolution: " << ( std::clock() - n ) * 1000.0 / CLOCKS_PER_SEC << " millisecs    "  ;
            }
            
            std::stack<int> stk  ;

            const auto start = std::clock() ;
            for( std::size_t i = 0 ; i < N ; ++i ) stk.push(i) ;
            const auto end = std::clock() ;

            std::cout << "total time: " << ( end - start ) * 1000.0 / CLOCKS_PER_SEC << " millisecs\n"
                      <<   "\tamortised time to push one item: "
                      << ( ( end - start ) * 1'000'000'000.0 / CLOCKS_PER_SEC ) / N << " nanosecs\n\n" ;
        }
        catch( const std::exception& ) { return 1 ; }
    }
}
