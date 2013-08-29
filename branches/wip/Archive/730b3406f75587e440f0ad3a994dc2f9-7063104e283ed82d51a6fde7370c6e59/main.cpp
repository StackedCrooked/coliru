#include <cstddef>
#include <cstdint>
#include <iostream>

std::uint32_t hash(std::uint64_t x) {
    return (x >> 32) ^ x;
}

int main() {
    for (std::size_t i = 0; i < 100; ++i) {
        std::cout << (hash(reinterpret_cast<std::uint64_t>(new int)) % 100) << '\n';
    }
}
