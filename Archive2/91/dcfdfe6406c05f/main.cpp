#include <iostream>

constexpr int i = 42;

namespace {
    char v[i];
    constexpr int i = 13;
}

template <typename T, std::size_t N>
constexpr std::size_t size(T (&)[N]) {
    return N;
}

int main() {
    std::cout << size(v) << '\n';
}
