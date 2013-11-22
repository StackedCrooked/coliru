#include <iostream>
#include <cstdint>
#include <bitset>
#include <string>
#include <vector>

std::string to_string( const std::uint8_t* a, std::size_t n )
{
    std::string result ;

    using bits = std::bitset<8> ;
    for( std::size_t i = 0 ; i < n ; ++i ) result += bits( a[i] ).to_string() ;

    return result ;
}

template< std::size_t NBITS >
std::vector<std::uint8_t> to_n_bit_values( const std::string& str )
{
    std::vector<std::uint8_t> result ;

    using bits = std::bitset<NBITS> ;
    for( std::size_t i = 0 ; i < str.size() ; i += NBITS )
        result.push_back( bits( str.substr( i, NBITS ) ).to_ulong() ) ;

    return result ;
}

template< std::size_t NBITS = 6 >
std::vector<std::uint8_t> to_n_bit_values( const std::uint8_t* a, std::size_t n )
{ return to_n_bit_values<NBITS>( to_string(a,n) ) ; }

int main() // minimal test driver
{
    constexpr std::size_t N = 6 ;
    const std::uint8_t a[N] = { 0, 1, 25, 3, 255, 49 } ;
    for( int i : a ) std::cout << i << ' ' ;
    std::cout << '\n' ;

    std::string str = to_string(a,N) ;
    for( std::size_t i = 0 ; i < str.size() ; i += 8 )
        std::cout << str.substr( i, 8 ) << ' ' ;
    std::cout << '\n' ;

    for( std::size_t i = 0 ; i < str.size() ; i += 6 )
        std::cout << str.substr( i, 6 ) << ' ' ;
    std::cout << '\n' ;

    for( auto i : to_n_bit_values<>(a,N) ) std::cout << int(i) << ' ' ;
    std::cout << '\n' ;
}
