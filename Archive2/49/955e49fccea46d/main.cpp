#include <iostream>
#include <array>

auto dependent_return_type(std::size_t size) -> std::array<int, size> {
    std::array<int, size> return_value;
    for(int i = 0; i < size; i++) {
        return_value[i] = i;
    }
    return return_value;
}

int main() {
    auto foo = dependent_return_type(10);
    for(i : foo) {
        std::cout << i << "\n";
    }
    return 0;
}