#include <vector>
#include <type_traits>
#include <iostream>

int main() {
    std::cout << std::is_default_constructible<std::vector<int>>::value;        
}