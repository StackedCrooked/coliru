#include <type_traits>
#include <iostream>

int main () {
    std::cout << std::boolalpha << std::is_const<const void*>::value << std::endl;
    std::cout << std::boolalpha << std::is_const<const void* const>::value << std::endl;
}