#include <type_traits>
#include <iostream>

int main() {
    std::cout << std::integral_constant<std::nullptr_t, nullptr>::value;
}