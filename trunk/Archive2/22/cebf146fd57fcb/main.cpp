#include <iostream>
#include <cmath>
#include <cerrno>
#include <cstring>
#include <cfenv>
#pragma STDC FENV_ACCESS ON
int main()
{
    std::cout << "log10(1000) = " << std::log10(1000) << '\n'
              << "log10(0.001) = " << std::log10(0.001) << '\n'
              << "base-5 logarithm of 125 = " << std::log10(125)/std::log10(5) << '\n';
    // special values
    std::cout << "log10(1) = " << std::log10(1) << '\n'
              << "log10(+Inf) = " << std::log10(INFINITY) << '\n';
    // error handling 
    errno=0; std::feclearexcept(FE_ALL_EXCEPT);
    std::cout << "log10(0) = " << std::log10(0) << '\n';
    if(errno == ERANGE)
        std::cout << "    errno == ERANGE: " << std::strerror(errno) << '\n';
    if(std::fetestexcept(FE_DIVBYZERO))
        std::cout << "    FE_DIVBYZERO raised\n";
}