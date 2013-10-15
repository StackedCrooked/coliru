#include <boost/multiprecision/cpp_int.hpp>
#include <string>
#include <iostream>
#include <iomanip>

using int_t = boost::multiprecision::cpp_int ;

int_t reverse( const int_t& n )
{
    if( n < 0 ) return - reverse( -n ) ;
    else if( n < 10 ) return n ;
    else
    {
        std::string str = n.str() ;
        auto pos = str.find_last_not_of('0') ;
        if( pos != str.size() - 1 ) str = str.substr( 0, pos+1 ) ;
        return int_t( std::string( str.rbegin(), str.rend() ) ) ;
    }
}

int main()
{
    constexpr int width = 40 ;
    const auto setw = std::setw(width) ;

    const int_t i { "123456789012345678901234567890" } ;
    const int_t j = reverse(i) ;
    std::cout << setw << i << '\n' << setw << j << "\n\n" ;

    const int_t k = 111333555777999 ;

    std::cout << setw << j << " +\n"
               << setw << k << '\n'
               << std::string( width, '-' ) << '\n'
               << setw << j + k << '\n' ;
}
