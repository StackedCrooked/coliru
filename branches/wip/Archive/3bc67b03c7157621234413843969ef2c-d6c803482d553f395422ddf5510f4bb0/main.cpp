#include <iostream>

constexpr size_t pow(size_t base, size_t exponent) {
    return exponent == 1 ? base : (base * pow(base, exponent - 1));
}

int main() {
    static_assert(pow(10, 9) == 1000000000, "..");
}