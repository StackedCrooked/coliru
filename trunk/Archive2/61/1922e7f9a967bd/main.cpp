#include <iostream>
#include <limits>
#include <bitset>
#include <memory>
#include <string>
#include <vector>

template < typename T > void show_bytes( const T& object, const char* tag = nullptr )
{
    using byte = unsigned char ;
    constexpr auto BITS_PER_BYTE = std::numeric_limits<byte>::digits ;
    using byte_bits = std::bitset<BITS_PER_BYTE> ;

    const auto n = sizeof(T) ;
    const byte* const pbyte = reinterpret_cast< const byte* >( std::addressof(object) ) ;

    for( std::size_t i = 0 ; i<n ; ++i ) std::cout << byte_bits( pbyte[i] ) << ' ' ;
    if(tag) std::cout << " (" << tag << ')' ;
    std::cout << "\n\n" ;
}

#define SHOW_BYTES(a) show_bytes( a, #a ) ;

int main()
{
    SHOW_BYTES( 12345 ) ; // int
    SHOW_BYTES( short(12345) ) ; // short
    SHOW_BYTES( (unsigned long long)(12345) ) ; // unsigned long long

    std::string string = "hello world!" ;
    SHOW_BYTES( string ) ; // string
    string.reserve(1000) ;
    SHOW_BYTES( string ) ; // string
    string += "!!!" ;
    SHOW_BYTES( string ) ; // string

    double dbl = 0 ;
    SHOW_BYTES( dbl ) ; // double
    dbl = 1234.56 ;
    SHOW_BYTES( dbl ) ; // double
    dbl = 123456789.123 ;
    SHOW_BYTES( dbl ) ; // double
    SHOW_BYTES( float(dbl) ) ; // float

    std::vector<float> vector { 1, 2, 3, 4 } ;
    SHOW_BYTES( vector ) ; // vector

    SHOW_BYTES( std::cin ) ; // stream
}
