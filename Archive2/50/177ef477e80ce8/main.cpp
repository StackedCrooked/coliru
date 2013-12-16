#include <cstddef>
#include <iostream>

std::size_t constexpr max(std::size_t a) {
    return a;
}

std::size_t constexpr max(std::size_t a, std::size_t b) {
    return a > b ? a : b;
}

template<typename... Ts>
std::size_t constexpr max(std::size_t a, std::size_t b, Ts... xs) {
    return max(max(a, b), xs...);
}

template<typename... Args>
std::size_t constexpr max_size() {
    return max(sizeof(Args)...);
}

int main() {
    std::cout << max_size<char, short, int>() << '\n';
}
