#include <iostream>
#include <string>
#include <type_traits>
#include <sstream>
#include <iomanip>
#include <locale>
#include <limits>

template < typename T >
typename std::enable_if< std::is_floating_point<T>::value, std::string >::type
decimal_part( T number, int ndigits = 6 )
{
    if( ndigits < 1 ) return "" ;

    std::ostringstream stm ;
    stm << std::fixed << std::setprecision(ndigits) << number ;
    auto str = stm.str() ;
    return str.substr( str.find( std::use_facet< std::numpunct<char> >( stm.getloc() ).decimal_point() ) + 1 ) ;
}

int main()
{
    const double n = -2 / 3.0 ;
    std::cout << decimal_part(n) << '\n' // 666667
              << decimal_part( n, 3 ) << '\n' // 667
              << decimal_part( n, 8 ) << '\n' // 66666667
              << decimal_part( n, std::numeric_limits<double>::digits10 ) << '\n' ; // 666666666666667 (typical)
}
