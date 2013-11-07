#include <cstddef>
#include <iostream>
#include <string>

int main() {
    std::cout << sizeof(std::size_t) << '\n';
    std::cout << sizeof(char*) << '\n';
    std::cout << sizeof(std::string) << '\n';
    return 0;
}
