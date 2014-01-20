#include <cmath>
#include <iostream>

int bits_n(int x) {
    if (x == 0) return 1;
    return std::ceil(std::log(x) / std::log(2));
}

int main() 
{
    std::cout << "0:" << bits_n(0) << '\n';
    std::cout << "1:" << bits_n(1) << '\n';
    std::cout << "2:" << bits_n(2) << '\n';
    std::cout << "4:" << bits_n(4) << '\n';
    std::cout << "7:" << bits_n(7) << '\n';
    std::cout << "12:" << bits_n(12) << '\n';
    std::cout << "42:" << bits_n(42) << '\n';
}