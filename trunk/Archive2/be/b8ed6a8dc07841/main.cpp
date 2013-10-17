#include <iostream>

template<typename T = int>
void print(const std::string& str) noexcept {
    std::cout << str << '\n';
}

int main() {
    print<>("hello");
    print("world");
    print<float>("yay");
}