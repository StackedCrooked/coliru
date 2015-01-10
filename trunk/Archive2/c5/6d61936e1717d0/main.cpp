#include <iostream>
#include <string>
#include <cstdint>
#include <iomanip>

int main( int argc, char* argv[] )
{
    const std::size_t N = 16 ;
    const std::size_t NHEXDIGITS = N * 2 ;

    if( argc != 2 )
    {
        std::cerr << "usage: " << argv[0] << " <" << N*8 << "-bit value as " << NHEXDIGITS << " hex digits>\n" ;
        return 1 ;
    }

    std::string hex = argv[1] ;
    if( hex.size() > NHEXDIGITS )
    {
        std::cerr << "too many hex digits\n" ;
        return 1 ;
    }

    std::cout << "command line argument: " << hex << '\n' ;
    // if less than N digits, pad with zeroes on the left
    if( hex.size() < NHEXDIGITS ) hex = std::string( NHEXDIGITS - hex.size(), '0' ) + hex ;

    std::uint8_t octets[N]{} ;

    for( std::size_t i = 0 ; i < N ; ++i )
    {
        try
        {
            // convert each octet (two characters) to an integer
            // http://en.cppreference.com/w/cpp/string/basic_string/stoul
            octets[i] = std::stoul( hex.substr( i*2, 2 ), nullptr, 16 ) ;
        }
        catch( const std::exception& )
        {
            std::cerr << "command line parse error\n" ;
            return 1 ;
        }
    }

    std::cout << "octets: " << std::hex ;
    for( unsigned int v : octets ) std::cout << std::setw(2) << std::setfill('0') << v << ' ' ;
    std::cout << '\n' ;
}
