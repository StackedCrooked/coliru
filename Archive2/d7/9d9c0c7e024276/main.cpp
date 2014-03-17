#include <iostream>

struct Foo {
    Foo(int) {}
};

int main() {
    auto&& f = Foo(5);
    std::cout << &f;
    return 0;
}