#include <cstddef>
#include <type_traits>

#include <iostream>
#include <array>

int main () {
    
    std::cout << std::rank<std::array<int, 1>>::value << std::endl;
    
}