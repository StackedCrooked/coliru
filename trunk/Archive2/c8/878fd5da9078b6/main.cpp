#include <iostream>
#include <fstream>
#include <iomanip>

int main()
{
    const char* const file_name = "test.bin" ;

    // create a test file, put some bytes (including zeroes) into it
    {
        std::ofstream file( file_name, std::ios::binary ) ;
        for( int i = 0 ; i < 300 ; ++i ) file << char( i%7 ) ;
    }

    // read the contents of the file into a string
    std::string str ;
    {
        std::ifstream file( file_name, std::ios::binary ) ; // open file for input
        
        // copy the contents of the file to a to a C++ string 
        char c ;
        while( file.get(c) ) str += c ; 
    }

    const char* buffer = str.c_str() ; // pointer to first char in the string
    const auto nchars = str.size() ; // number of bytes that were read

    // print out the values of the bytes in the buffer
    for( std::size_t i = 0 ; i < nchars ; ++i )
    {
        std::cout << std::setw(2) << int( buffer[i] ) << ' ' ;
        if( i%40 == 39 ) std::cout << '\n' ;
    }
    std::cout << '\n' ;
}
