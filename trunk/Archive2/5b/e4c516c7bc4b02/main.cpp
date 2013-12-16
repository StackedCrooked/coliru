#include <iostream>

constexpr bool f(int x) {
    return bool(std::cout << x);
}

int main() {}