#include <cmath>
#include <iostream>

int main()
{
    double value = 1.21077;
    std::cout
        << (double)(value * std::pow(10.0, 5)) << '\n'
        << static_cast<int>(value * std::pow(10.0, 5)) << '\n';
}
