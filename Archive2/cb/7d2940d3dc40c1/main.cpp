#include <iostream>

struct base { virtual void foo() { std::cout << "Base!\n"; } };
struct derived : base { virtual void foo() override { std::cout << "Derived!\n"; } };

int main() {
    base sliced = derived{};
    sliced.foo();
}