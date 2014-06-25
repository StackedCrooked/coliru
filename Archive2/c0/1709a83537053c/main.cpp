#include <iostream>
#include <cmath>
#include <cfloat>
#include <cerrno>
#include <cfenv>
#include <cstring>
#pragma STDC FENV_ACCESS ON
int main()
{
    std::cout << "acosh(1) = " << std::acosh(1) << '\n'
              << "acosh(10) = " << std::acosh(10) << '\n'
              << "acosh(DBL_MAX) = " << std::acosh(DBL_MAX) << '\n'
              << "acosh(Inf) = " <<  std::acosh(INFINITY) << '\n';
     // error handling 
     errno = 0; std::feclearexcept(FE_ALL_EXCEPT);
     std::cout << "acosh(0.5) = " << std::acosh(0.5) << '\n';
     if(errno == EDOM)
         std::cout << "    errno == EDOM: " << std::strerror(errno) << '\n';
     if(std::fetestexcept(FE_INVALID))
        std::cout << "    FE_INVALID raised\n";
}