#include <iostream>

template <typename T, std::size_t N>
constexpr std::size_t size(T (&)[N]) {
    return N;
}

int main() {
    constexpr int i = 42;

    {
        char v[i];
        constexpr int i = 13;
        std::cout << size(v) << '\n';
    }
}
