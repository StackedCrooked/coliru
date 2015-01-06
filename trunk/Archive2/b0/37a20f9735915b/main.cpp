#include <cmath>
#include <limits>
#include <iomanip>
#include <iostream>
#include <type_traits>
#include <algorithm>
 
int CompareDoubleAbsoulte(double x, double y, double absTolerance = (1.0e-8))
{
    double diff = x - y;
    if (fabs(diff) <= absTolerance)
        return 0;

    return (diff > 0) ? 1 : -1;
}


int main()
{
    double d1 = 0.2;
    double d2 = 1 / std::sqrt(5) / std::sqrt(5);
 
    if(d1 == d2)
            std::cout << "d1 == d2\n";
    else
            std::cout << "d1 != d2\n";

    if(CompareDoubleAbsoulte(d1, d2))
            std::cout << "d1 almost equals d2\n";
    else
            std::cout << "d1 does not almost equal d2\n";
}