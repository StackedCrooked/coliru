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

    // place the contents of the file into a buffer (const char*)
    std::string buff ;
    {
        std::ifstream file( file_name, std::ios::binary ) ; // open file for input
        
        // copy the contents of the file to a to a C++ string 
        char c ;
        while( file.get(c) ) buff += c ; 
    }

    const char* buffer = buff.c_str() ; // pointer to first char in the string
    const auto nchars = buff.size() ; // number of bytes that wrre read

    // print out the values of the bytes in the buffer
    for( std::size_t i = 0 ; i < nchars ; ++i )
    {
        std::cout << std::setw(2) << int( buffer[i] ) << ' ' ;
        if( i%40 == 39 ) std::cout << '\n' ;
    }
    std::cout << '\n' ;
}
