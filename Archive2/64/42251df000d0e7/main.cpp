#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
int main()
{
    std::cout << "default precision (6): " << 3.0500346 << '\n';
    std::cout << "std::precision(10):    " << std::setprecision(10) << 3.0500346 << '\n';
    
    return 0;
}