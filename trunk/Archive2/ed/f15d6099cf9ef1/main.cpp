#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
int main()
{
    //const long double pi = std::acos(-1.L);
    const long double pi = 6283185.0;
    std::cout << "default precision (6): " << pi << '\n'
              << "std::precision(10):    " << std::setprecision(10) << pi << '\n'
              << "digits 10: " << std::numeric_limits<double>::digits10 << '\n'
              << "max digits 10: " << std::numeric_limits<double>::max_digits10 << '\n'
              << pi << '\n';
}