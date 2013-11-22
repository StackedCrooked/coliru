#include <iostream>
#include <cmath>
#include <typeinfo>

int main()
{
    std::cout << std::pow(0,0) << std::endl ;
    std::cout <<  errno << ":" << EDOM << std::endl ;
    std::cout << typeid( std::pow(0,0) ).name() << std::endl ;
    std::cout << __STDC_IEC_559__ << std::endl ;
}