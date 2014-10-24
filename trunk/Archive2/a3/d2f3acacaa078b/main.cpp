#include <iostream>

template<typename T>
auto add(const T& x, const T& y) -> decltype(x + y) {
    return x + y;
}

template<typename T>
auto add(const T& x, const T& y) -> decltype(x.add(y)) {
    return x.add(y);
}

int main() {
    std::cout << add(10, 11);
}