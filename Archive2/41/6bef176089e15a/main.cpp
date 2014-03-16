#include <iostream>

struct Foo {
    Foo(int) {}
};

int main() {
    std::cout << std::addressof(Foo(5));
    return 0;
}