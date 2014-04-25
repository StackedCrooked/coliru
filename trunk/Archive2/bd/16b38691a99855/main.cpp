#include <iostream>
#include <string>

template<typename T>
constexpr auto add(T&& x, T&& y) -> decltype(std::forward<T>(x) + std::forward<T>(y)) {
    return std::forward<T>(x) + std::forward<T>(y);
}

int main() {
    std::cout << add(10, 11) << '\n'
              << add(10.f, 12.f) << '\n'
              << add(std::string("Hello"), std::string(" World")) << '\n';
}