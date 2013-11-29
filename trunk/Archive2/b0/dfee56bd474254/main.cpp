#include <iostream>
#include <string>
#include <sstream>
#include <complex>

struct stringify
{
    operator std::string() const { return str ; }
    std::string str ;
};

template < typename T > stringify operator+ ( stringify s, const T& object )
{
    std::ostringstream stm ;
    stm << object ;
    if( !s.str.empty() && !std::isspace( *s.str.rbegin() ) ) s.str += ' ' ;
    s.str += stm.str() ;
    return s ;
}

int main()
{
    std::complex<double> c( 1.23,3.45) ;

    const std::string str = stringify() + "The string and values" + 1 + 2 +
                            " stuff is not the same each time." + '\n' + c +
                            5.789 + " I am looking for a function that " + '\n' ;

    std::cout << str ;
}
