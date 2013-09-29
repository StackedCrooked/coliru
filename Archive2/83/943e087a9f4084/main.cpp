#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::is_same<decltype(1 - 1), signed>() << '\n';
    std::cout << std::is_same<decltype(1u - 1u), unsigned>() << '\n';
    return 0;
}
