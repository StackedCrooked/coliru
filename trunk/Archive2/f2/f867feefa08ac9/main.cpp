#include <iostream>
#include <bitset>
#include <limits>

// using byte = unsigned char ;
// constexpr std::size_t BITS_PER_BYTE = std::numeric_limits<byte>::digits ;

typedef unsigned char byte ;
const std::size_t BITS_PER_BYTE = std::numeric_limits<byte>::digits ;

// return the bits in a byte as a string of zeroes and ones
std::string to_bits( byte b )
{ return std::bitset<BITS_PER_BYTE>(b).to_string() ; }

std::string to_bits( const std::string& text )
{
    std::string result ;
    
    // for( byte b : text ) result += to_bits(b) ;
    for( std::size_t i = 0 ; i < text.size() ; ++i ) result += to_bits( text[i] ) ;
    
    return result ;
}

int main()
{
    const std::string  bits = to_bits( "Atton (5)" ) ;
    for( std::size_t i = 0 ; i < bits.size() ; i += BITS_PER_BYTE )
        std::cout << bits.substr( i, BITS_PER_BYTE ) << ' ' ;
    std::cout << '\n' ;
}
