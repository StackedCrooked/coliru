#include <iostream>

template <typename ...Args>
void foo(Args... args);

template <>
void foo(int i) {
    std::cout << i << std::endl;
}

int main() {
    foo<>(1);
}
