#include <iostream>
#include <cmath>
#include <cerrno>
#include <cfenv>
#include <cstring>
 
#pragma STDC FENV_ACCESS ON
 
int main()
{
    // normal use
    std::cout << "sqrt(100) = " << std::sqrt(100) << '\n'
              << "sqrt(2) = " << std::sqrt(2) << '\n'
              << "golden ratio = " << (1+std::sqrt(5))/2 << '\n';
    // special values
    std::cout << "sqrt(-0) = " << std::sqrt(-0.0) << '\n';
    // error handling
    errno = 0; std::feclearexcept(FE_ALL_EXCEPT);
    std::cout << "sqrt(-1.0) = " << std::sqrt(-1) << '\n';
    if(errno == EDOM)
        std::cout << "    errno = EDOM " << std::strerror(errno) << '\n';
    if(std::fetestexcept(FE_INVALID))
        std::cout << "    FE_INVALID raised\n";
}