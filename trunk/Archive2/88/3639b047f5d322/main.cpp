#include <cmath>
#include <iostream>
 
int main()
{
    std::cout << std::fixed;
    std::cout << std::ceil(12.0) << '\n';
    std::cout << std::ceil(12.1) << '\n';
    std::cout << std::ceil(12.5) << '\n';
    std::cout << std::ceil(12.9) << '\n';
    std::cout << std::ceil(13.0) << '\n';
}