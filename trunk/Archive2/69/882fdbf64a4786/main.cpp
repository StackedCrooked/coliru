#include <iostream>
#include <cmath>
#include <cerrno>
#include <cfenv>
 
#pragma STDC FENV_ACCESS ON
const double pi = std::acos(-1);
int main()
{
    // typical usage
    std::cout << "tan  (pi/4) = " << std::tan(  pi/4) << '\n' // 45 deg.
              << "tan(3*pi/4) = " << std::tan(3*pi/4) << '\n' // 135 deg
              << "tan(5*pi/4) = " << std::tan(5*pi/4) << '\n' // -135 deg
              << "tan(7*pi/4) = " << std::tan(7*pi/4) << '\n'; // -45 deg
    // special values
    std::cout << "tan(+0) = " << std::tan(0.0) << '\n'
              << "tan(-0) = " << std::tan(-0.0) << '\n';
    // error handling 
    std::feclearexcept(FE_ALL_EXCEPT);
    std::cout << "tan(INFINITY) = " << std::tan(INFINITY) << '\n';
    if(std::fetestexcept(FE_INVALID)) std::cout << "    FE_INVALID raised\n";
}