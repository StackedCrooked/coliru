#include <iostream>

int main() {
    int x = 10;
    void* l = &x;
    std::cout << l << '\n';
    size_t i = reinterpret_cast<size_t>(l);
    std::cout << std::hex << i << '\n';
}