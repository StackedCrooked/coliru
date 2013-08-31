#include <cstdint>
#include <limit>

#include <iostream>

int main() {
    auto x = std::numeric_limits<std::int32_t>::max();
    std::cout << -x;
}