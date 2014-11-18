#include <iostream>
#include <cmath>

constexpr double sqrtThree = 1.73205080757;

constexpr unsigned long long Equilateral(bool swap = true, int count = 1) {
    return count > 15 ? 0 
        : ((std::pow(2 + sqrtThree, count) 
        + std::pow(2 - sqrtThree, count) ) 
        + (swap ? 2 : -2)) + Equilateral(!swap, ++count);
}


int main() {
    std::cout << Equilateral();
}