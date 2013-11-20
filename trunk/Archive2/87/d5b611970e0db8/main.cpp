#include <iostream>
#include <bitset>
#include <string>
#include <vector>

typedef unsigned char byte ;

std::string to_string( const byte* a, std::size_t n )
{
    std::string result ;

    typedef std::bitset<8> bits ;
    for( std::size_t i = 0 ; i < n ; ++i ) result += bits( a[i] ).to_string() ;

    return result ;
}

template< std::size_t NBITS >
std::vector<byte> to_n_bit_values( const std::string& str )
{
    std::vector<byte> result ;

    typedef std::bitset<8> bits ;
    for( std::size_t i = 0 ; i < str.size() ; i += NBITS )
        result.push_back( bits( str.substr( i, NBITS ) ).to_ulong() ) ;

    return result ;
}

template< std::size_t NBITS >
std::vector<byte> to_n_bit_values( const byte* a, std::size_t n )
{ return to_n_bit_values<NBITS>( to_string(a,n) ) ; }

int main() // minimal test driver
{
    const std::size_t N = 6 ;
    const byte a[N] = { 0, 1, 25, 3, 255, 49 } ;
    for( std::size_t i = 0 ; i < N ; ++i ) std::cout << int( a[i] ) << ' ' ;
    std::cout << '\n' ;

    std::string str = to_string(a,N) ;
    for( std::size_t i = 0 ; i < str.size() ; i += 8 )
        std::cout << str.substr( i, 8 ) << ' ' ;
    std::cout << '\n' ;

    for( std::size_t i = 0 ; i < str.size() ; i += 6 )
        std::cout << str.substr( i, 6 ) << ' ' ;
    std::cout << '\n' ;

    const std::vector<byte> six_bit_values = to_n_bit_values<6>(a,N) ;
    for( std::size_t i = 0 ; i < six_bit_values.size() ; ++i )
        std::cout << int( six_bit_values[i] ) << ' ' ;
    std::cout << '\n' ;
}
