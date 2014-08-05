#include <type_traits>
#include <iostream>

int main() {
    std::cout << std::is_constructible<int>::value << "\n";
    std::cout << std::is_default_constructible<int>::value << "\n";

    // std::cout << std::is_trivially_copyable<int>::value << "\n";
    std::cout << std::has_trivial_copy_constructor<int>::value << "\n";
}
