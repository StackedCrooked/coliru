#include <iostream>
#include <fstream>
#include <bitset>

int main()
{
    // open the file
    std::ifstream file( __FILE__, std::ios::binary ) ;
    file >> std::noskipws ; // do not skip whitespace characters
    
    unsigned char byte ;
    int n = 0 ;
    
    while( file >> byte ) // for each byte in the file
    {
        // print out the bits
        std::cout << std::bitset< std::numeric_limits<unsigned char>::digits >(byte) << ' ' ; 
        if( ( n++ % 16 ) == 15 ) std::cout << '\n' ; // 16 bytes per line
    }
}
