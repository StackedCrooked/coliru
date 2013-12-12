#include <iostream>
#include <cstdlib>
#include <string>

int main()
{
    std::string str = "0.0" ;
    double d = std::atof( str.c_str() ) ;
    std::cout << d << ' ' ;
    d = std::stod(str) ;
    std::cout << d << '\n' ;

    str = "-12.345" ;
    d = std::atof( str.c_str() ) ;
    std::cout << d << ' ' ;
    d = std::stod(str) ;
    std::cout << d << '\n' ;

    str = "+Infinity" ;
    d = std::atof( str.c_str() ) ;
    std::cout << d << ' ' ;
    d = std::stod(str) ;
    std::cout << d << '\n' ;
}
