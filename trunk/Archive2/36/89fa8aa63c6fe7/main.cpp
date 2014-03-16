#include <iostream>

struct Foo {
    Foo(int) {}
};

int main() {
    std::cout << std::address_of(Foo(5));
    return 0;
}