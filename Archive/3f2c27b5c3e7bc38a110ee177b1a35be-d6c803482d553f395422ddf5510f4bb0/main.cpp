#include <iomanip>
#include <iostream>
#include <limits>

int main() {
    std::cout << "Bits: " << sizeof(long double) * 8 << '\n';
    std::cout << std::fixed << std::setprecision(45) << std::numeric_limits<long double>::max();
}