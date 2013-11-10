#include <iostream>
#include <array>
    
template<typename ret, typename... T> std::array<ret, sizeof...(T)> make_array(T&&... refs) {
    return std::array<ret, sizeof...(T)>{ { std::forward<T>(refs)... } };
}

int main() {
    auto arr = make_array(1, 2, 3, 5);
    for (const auto i : arr) std::cout << i << '\n';
}