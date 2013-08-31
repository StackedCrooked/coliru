#include <iostream>
#include <cmath>

constexpr double pi = atan(1.0)*4.0;

int main()
{
    std::cout << "Enter radius: ";
    double r;
    std::cin >> r;
    auto S = pi*r*r;
    std::cout << "Area is: " << S << "\n";
} 
