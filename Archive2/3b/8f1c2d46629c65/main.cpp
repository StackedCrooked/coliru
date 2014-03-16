#include <iostream>

struct Foo {
    Foo(int) {}
};

template<typename T> auto addressof(T&& rvalue) -> decltype(&rvalue) {
    return &rvalue;
}

int main() {
    std::cout << addressof(Foo(5));
    return 0;
}