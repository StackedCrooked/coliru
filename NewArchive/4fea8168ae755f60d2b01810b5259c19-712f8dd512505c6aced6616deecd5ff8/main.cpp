#include <iostream>

template<typename T>
void f(T v) {
    std::cout << v << '\n';
}

template<>
void f<int16_t>(int16_t v) {
    std::cout << v << '\n';
}

template<>
void f<int32_t>(int32_t v) {
    std::cout << v << '\n';
}

int main() {
    int32_t v = 100;
    f(v);
}