#include <cmath>
#include <iostream>
 
int main()
{
    std::cout << std::fixed;
    std::cout << std::floor(12.0) << '\n';
    std::cout << std::floor(12.1) << '\n';
    std::cout << std::floor(12.5) << '\n';
    std::cout << std::floor(12.67777) << '\n';
    std::cout << std::floor(12.9) << '\n';
    std::cout << std::floor(13.0) << '\n';
}