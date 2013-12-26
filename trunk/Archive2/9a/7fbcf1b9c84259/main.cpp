#include <iostream>
#include <fstream>
#include <algorithm>

int main()
{
    const char* path = "asd.txt" ;

    // overwrite the file with new values
    {
        std::ofstream file(path) ;
        for( int i = 10 ; i < 50 ; i += 5 ) file << i << '\n' ;
    }

    // to check it out: dump the contents of the file to stdout
    std::cout << std::ifstream(path).rdbuf() << "-------------\n" ;

    // append new values to end of file
    {
        std::ofstream file( path, std::ios_base::app ) ;
        for( int i = 70 ; i < 100 ; i += 10 ) file << i << '\n' ;
    }

    std::cout << std::ifstream(path).rdbuf() << "-------------\n" ;

    // modify values in memory and re-write the file with the new values
    {
        const std::size_t MAX_SIZE = 1024 ; // maximum possible number of values
        std::size_t actual_size = 0 ; // actual number of values, initially zero
        int values[MAX_SIZE] ;

        // read the contents into memory
        {
            std::ifstream file(path) ;
            int v ;
            while( file >> v && actual_size < MAX_SIZE )
                values[ actual_size++ ] = v ;
        }

        // modify the contents in memory as desired

        std::reverse( values, values+actual_size ) ; // reverse the order

        if( actual_size < MAX_SIZE ) // if there is space
            values[ actual_size++ ] = 500 ; // append 500 at the end

        // replace 25 with 666
        std::replace( values, values+actual_size , 25, 666 ) ;

        // add 30 to every value
        for( std::size_t i = 0 ; i < actual_size ; ++i ) values[i] += 30 ;

        // overwrite the file with the modified contents
        {
            std::ofstream file(path) ;
            for( std::size_t i = 0 ; i < actual_size ; ++i ) file << values[i] << '\n' ;
        }
    }

    std::cout << std::ifstream(path).rdbuf() << "-------------\n" ;
}
