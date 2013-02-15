#include <type_traits>
#include <iostream>

int main() {
    std::cout << (bool)std::integral_constant<std::nullptr_t, nullptr>::value;
}