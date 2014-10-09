#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
int main()
{
    const long double pi = 0.1234567;
    std::cout << "default precision (6): " << pi << '\n'
              << "std::precision(8):    " << std::setprecision(8) << pi << '\n';
              
    const long double qu = 0.2345678901;
    std::cout << qu << '\n';
}