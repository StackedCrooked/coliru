#include <iostream>
#include <cmath>
#include <cerrno>
#include <cfenv>
#include <cstring>

int main()
{
    // typical usage
    std::cout << "pow(2, 10) = " << std::pow(2,10) << '\n'
              << "pow(2, 0.5) = " << std::pow(2,0.5) << '\n'
              << "pow(5, -1) = " << std::pow(-5,-1) << '\n';
    // special values
    std::cout << "pow(-1, NAN) = " << std::pow(-1,NAN) << '\n'
              << "pow(+1, NAN) = " << std::pow(+1,NAN) << '\n'
              << "pow(INFINITY, 2) = " << std::pow(INFINITY, 2) << '\n'
              << "pow(INFINITY, -1) = " << std::pow(INFINITY, -1) << '\n';
    // error handling 
    errno = 0; std::feclearexcept(FE_ALL_EXCEPT);
    std::cout << "pow(-1, 1/3) = " << std::pow(-1, 1.0/3) << '\n';
    if(errno == EDOM) std::cout << "    errno == EDOM " << std::strerror(errno) << '\n';
    if(std::fetestexcept(FE_INVALID)) std::cout << "    FE_INVALID raised\n";
 
    std::feclearexcept(FE_ALL_EXCEPT);
    std::cout << "pow(-0, -3) = " << std::pow(-0.0, -3) << '\n';
    if(std::fetestexcept(FE_DIVBYZERO)) std::cout << "    FE_DIVBYZERO raised\n";
}