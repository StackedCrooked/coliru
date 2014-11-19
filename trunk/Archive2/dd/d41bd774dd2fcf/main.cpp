#include <iostream>
#include <cmath>
#include <cerrno>
#include <cfenv>
 
#pragma STDC FENV_ACCESS ON
const double pi = std::acos(-1);
int main()
{
    // typical usage
    std::cout << "sin(pi/6) = " << std::sin(pi/6) << '\n'
              << "sin(pi/2) = " << std::sin(pi/2) << '\n'
              << "sin(-3*pi/4) = " << std::sin(-3*pi/4) << '\n';
    // special values
    std::cout << "sin(+0) = " << std::sin(0.0) << '\n'
              << "sin(-0) = " << std::sin(-0.0) << '\n';
    // error handling 
    std::feclearexcept(FE_ALL_EXCEPT);
    std::cout << "sin(INFINITY) = " << std::sin(INFINITY) << '\n';
    if(std::fetestexcept(FE_INVALID)) std::cout << "    FE_INVALID raised\n";
}