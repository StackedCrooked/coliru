#include <iostream>
#include <string>

template<typename T>
T add(T x, T y) {
    return x + y;
}

int main() {
    std::cout << add(10, 11) << '\n'
              << add(10.f, 12.f) << '\n'
              << add(std::string("Hello"), std::string(" World")) << '\n';
}