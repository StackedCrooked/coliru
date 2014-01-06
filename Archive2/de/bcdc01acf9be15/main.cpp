#include <type_traits>
#include <iostream>

typedef int GLuint;

int main () {
    GLuint a = nullptr;
    std::cout << std::boolalpha << std::is_const<const void*>::value << std::endl;
    std::cout << std::boolalpha << std::is_const<const void* const>::value << std::endl;
}