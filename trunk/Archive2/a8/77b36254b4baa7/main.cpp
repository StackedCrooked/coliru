#include <iostream>
#include <string>

constexpr int factorial(int i) {
    return (i != 0)
        ? i * factorial(i - 1)
        : 1;
}

auto main() -> int {
    return 0;
}