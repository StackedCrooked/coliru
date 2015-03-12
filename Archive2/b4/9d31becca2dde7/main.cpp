#include <iostream>
#include <cstdint>
#include <vector>

auto components_of(int value) -> std::vector<int> {
    auto result = std::vector<int>();
    
    for (auto addend = 1; value != 0; addend <<= 1, value >>= 1) {
        if (value & 1) {
            result.push_back(addend);
        }
    }
    
    return result;
}

int main() {
    auto numbers = components_of(5);
    
    for (auto&& i : numbers) {
        std::cout << i << " ";
    }
}