#include <cmath>
#include <iostream>

int main() {
    auto n = 1000000000.0;
    for (long double x = 0.0; x < 1000.0 * n; x += n) {
        std::cout << std::abs((long double)std::sqrt(x) * (long double)std::sqrt(x) - x) << '\n';
    }
}