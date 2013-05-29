#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>

int main() {
    const std::size_t BUFFER_SIZE = 10;
    std::uint8_t fakeBuffer[BUFFER_SIZE];
    std::uint8_t *buffer = fakeBuffer;
    
    std::generate_n(buffer, BUFFER_SIZE, std::rand);
    
    for (std::size_t i = 0; i < BUFFER_SIZE; ++i) {
        std::cout << static_cast<int>(buffer[i]) << ' ';
    }
}