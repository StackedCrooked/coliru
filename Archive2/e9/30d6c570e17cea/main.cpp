#include <iostream>
#include <cmath>
#include <cfloat>
 
int main()
{
    std::cout << std::boolalpha
              << "isnan(NaN) = " << std::isnan(NAN) << '\n'
              << "isnan(Inf) = " << std::isnan(INFINITY) << '\n'
              << "isnan(0.0) = " << std::isnan(0.0) << '\n'
              << "isnan(DBL_MIN/2.0) = " << std::isnan(DBL_MIN/2.0) << '\n'
              << "isnan(0.0 / 0.0)   = " << std::isnan(0.0/0.0) << '\n'
              << "isnan(Inf - Inf)   = " << std::isnan(INFINITY - INFINITY) << '\n';
}