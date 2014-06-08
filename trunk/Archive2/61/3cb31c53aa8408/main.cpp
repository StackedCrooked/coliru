#include <iostream>

struct A {
    int a, b;
};

struct B : A {
    B(int a, int b) : A{a, b} {}
};

int main() {
    int i = 0;
    A a{++i, ++i};
    B b{++i, ++i};
    std::cout << a.a << ", " << a.b<< ", " << b.a << ", " << b.b << '\n';
}