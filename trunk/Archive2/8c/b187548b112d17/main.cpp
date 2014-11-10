#include <iostream>
#include <cmath>
 
int main()
{
    // normal use
    std::cout << "cbrt(729) = " << std::cbrt(729) << '\n'
              << "cbrt(-0.125) = " << std::cbrt(-0.125) << '\n';
    // special values
    std::cout << "cbrt(-0) = " << std::cbrt(-0.0) << '\n'
              << "cbrt(+inf) = " << std::cbrt(INFINITY) << '\n';
}