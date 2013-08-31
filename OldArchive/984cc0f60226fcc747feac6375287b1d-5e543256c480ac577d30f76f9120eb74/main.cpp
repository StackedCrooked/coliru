#include <iostream>
#include <string>
#include <vector>

int main() {
    uint8_t data[42];
    std::cout << static_cast<unsigned char>(data) << std::endl;
}
