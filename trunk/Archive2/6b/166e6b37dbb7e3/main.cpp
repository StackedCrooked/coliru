#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>

int main()
{
    const long double pi = std::acos(-1.L);
    std::cout << "default precision (6):  " << pi << '\n'
              << "custom  presision (10): " << std::setprecision(10) << pi << '\n'
              << "but is it sticky?       " << pi << '\n';
              
    return 0;
}