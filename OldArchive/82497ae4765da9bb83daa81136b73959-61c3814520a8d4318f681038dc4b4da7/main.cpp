#include <iostream>

int main()
{
    std::cout << std::fixed;
    std::cout.precision(10000);
    std::cout << 1.81 << std::endl;
    std::cout << 1.81f << std::endl;
}