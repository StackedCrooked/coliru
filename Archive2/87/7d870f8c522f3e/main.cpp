#include <iostream>

template <typename T>
void foo(const T &) {
    std::cout << "const T & as arg" << std::endl;
}

template <typename T>
void foo(T &&) {
    std::cout << "T && as arg" << std::endl;
}

int main() {
    const int x = 456;
    int y = 123;
    foo(123);
    foo(x);
    foo(y);
}