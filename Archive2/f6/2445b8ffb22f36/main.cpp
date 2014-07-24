#include <iostream>
#include <cmath>

int main()
{
    double x=0.03;
    double y=0.00999999999999999;
    std::cout << std::fmod(x, y) << '\n';
}