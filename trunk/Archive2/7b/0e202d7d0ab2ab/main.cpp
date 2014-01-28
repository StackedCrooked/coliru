#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <algorithm>

// does not take care of c-style /* .... */ comments
// does not take care of compile time optioning (#ifdef)
// does not count lines in included files

int main( int argc, char* argv[] )
{
    if( argc == 2 ) // comment on non-empty line
    {
        int line_cnt = 0 ;

        std::ifstream file( argv[1] ) ;
        std::string line ;
        while( std::getline( file, line ) )
        {
            static const auto not_space = [] ( char c ) { return std::isspace(c) == 0 ; } ;
            const auto iter = std::find_if( line.begin(), line.end(), not_space ) ;

            if( iter != line.end() && std::search_n( iter, line.end(), 2, '/' ) != iter )
                ++line_cnt ;
        }

        // comment only line

        std::cout << "program: line count excluding comments and empty lines: " << line_cnt << '\n' ;
    }
}
