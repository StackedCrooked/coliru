#include <cmath>
#include <iostream>

int main() {
    auto n = 1000000000.0;
    for (auto x = 0.0; x < 1000.0 * n; x += n) {
        std::cout << std::abs(std::sqrt(x) * std::sqrt(x) - x) << '\n';
    }
}