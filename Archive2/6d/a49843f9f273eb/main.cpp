#include <iostream>

struct Foo {
    Foo(int) {}
    Foo* operator&() {
        return this;
    }
};

int main() {
    std::cout << &Foo(5);
    return 0;
}