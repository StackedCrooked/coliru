#include <fstream>
#include <iostream>
#include <memory>
#include <chrono>

int main()
{
    const char TAB = '\t' ;
    // values to be written into one line in the file
    // in the actual program, these would be the calculated values
    // volatile, because we do not want any super-smart optimization
    volatile double x[] = { 1.2345, 1.2345, 1.2345,  1.2345, 1.2345, 1.2345, 1.2345 };
    
    using clock = std::chrono::steady_clock ;
    using msecs = std::chrono::milliseconds ;
    using  std::chrono::duration_cast ;

    // for the actual tests, make this larger, say 1024*1024
    const int NLINES = 1024 * 64 ; 

    std::size_t sz = 1024 ;
    for( int i = 0 ; i < 10 ; ++i, sz *= 2 )
    {
        // allocate memory for the stream buffer
        std::unique_ptr< char[] > buf( new char[sz] ) ; 
        std::cout << "buffer size: " << sz ;

        std::ofstream file ; 
        file.rdbuf()->pubsetbuf( buf.get(), sz ) ; // set the buffer
        file.open( "test.txt" ) ; // and then open the file

        auto start = clock::now() ;
        for( int i = 0 ; i < NLINES ; ++i )
        {
            for( auto d : x ) file << d << TAB ;
            file << '\n' ;
        }
        file << std::flush ;
        auto end = clock::now() ;

        std::cout << " elapsed: " << duration_cast<msecs>(end-start).count()
                  << " milliseconds.\n" ;
    }
}
