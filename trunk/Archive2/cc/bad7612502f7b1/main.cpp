#include <algorithm>
#include <iostream>

int main() {
    uint64_t a, b;
    a = b = 0;
    auto x = std::min(a, a-b);
    std::cout << typeid(x).str() << "\n";
}