#include <cstddef>
#include <iostream>

int main() {
    std::size_t foo = 0xDEADBEEF;
    std::cout << std::hex << foo << std::endl;
}
