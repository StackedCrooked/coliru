#include <iostream>
#include <cstdint>

void f(uint32_t v) {
    std::cout << v << "\n";
}

void f(uint16_t v) {
    std::cout << v << "\n";
}

int main() {
    int32_t v = 100;
    f(v);
}