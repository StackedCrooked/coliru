#include <iostream>
#include <limits>
#include <type_traits>

int main() {
    int a = 42;
    int *p = &a;
    std::cout << std::numeric_limits<decltype(a)>::max() << '\n';
    std::cout << std::numeric_limits<decltype(p)>::max();
}