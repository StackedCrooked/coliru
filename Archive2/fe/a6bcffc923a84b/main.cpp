#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
//
// invariant: file contains at least one line
std::string random_line( const char* path )
{
    std::string selected ;
    std::ifstream file(path) ;
    //
    std::string line ;
    std::streamsize nlines = 0 ;
    while( std::getline( file, line ) )
    {
        ++nlines ;
        if( std::rand() % nlines == 0 ) selected = line ;
    }
    //
    return selected ;
}
//
int main()
{
    std::srand( std::time(0) ) ; // seed the C library lcg
    //
    for( int i = 0 ; i < 3 ; ++i ) // repeat thrice
    {
        // print out a random line selected from this file
        std::cout << random_line(__FILE__) << '\n' ;
    }
}
