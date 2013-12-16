#include <iostream>
#include <cstdlib>
#include <string>

int main()
{
    std::string str = "0.0" ;
    double d = std::atof( str.c_str() ) ;
    double e = std::stod(str) ;
    std::cout << d << ' ' << e  << '\n' ; // 0 0

    str = "-12.345" ;
    d = std::atof( str.c_str() ) ;
    e = std::stod(str) ;
    std::cout << d << ' ' << e  << '\n' ; // -12.345 -12.345

    str = "+Infinity" ;
    d = std::atof( str.c_str() ) ;
    e = std::stod(str) ;
    std::cout << d << ' ' << e  << '\n' ; // inf inf
}
