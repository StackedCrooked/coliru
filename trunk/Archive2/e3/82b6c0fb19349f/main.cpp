#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main()
{
    const char* path = "asd.txt" ;

    // overwrite the file with new values
    {
        std::ofstream file(path) ;
        for( int i : { 12, 14, 61, 32, 56 } ) file << i << '\n' ;
    }

    // to check it out: dump the contents of the file to stdout
    std::cout << std::ifstream(path).rdbuf() << "-------------\n" ;


    // append new values to end of file
    {
        std::ofstream file( path, std::ios_base::app ) ;
        for( int i : { 77, 55, 88 } ) file << i << '\n' ;
    }

    std::cout << std::ifstream(path).rdbuf() << "-------------\n" ;

    // modify values in memory and re-write the file with the new values
    {
        std::vector<int> values ;

        // read the contents into memory
        {
            std::ifstream file(path) ;
            int i ;
            while( file >> i ) values.push_back(i) ;
        }

        // modify the contents in memory as desired

        std::reverse( values.begin(), values.end() ) ; // reverse the order

        values.push_back(99) ; // append 99 at the end

        // replace 61 with 666
        std::replace( values.begin(), values.end(), 61, 666 ) ;

        // append values if they are not already present
        for( int i : { 12, 22, 32, 42 } )
            if( std::find( values.begin(), values.end(), i ) == values.end() )
                values.push_back(i) ;

        // overwrite the file with the modified contents
        {
            std::ofstream file(path) ;
            for( int i : values ) file << i << '\n' ;
        }
    }

    std::cout << std::ifstream(path).rdbuf() << "-------------\n" ;
}
