#include <iostream>
#include <cmath>

int main()
{
    {
        double d = 1. / 0;
        std::cout << std::isnan(d) << std::isinf(d) << '\n';
    }
    {
        double d = 0. / 0;
        std::cout << std::isnan(d) << std::isinf(d) << '\n';
    }
}
