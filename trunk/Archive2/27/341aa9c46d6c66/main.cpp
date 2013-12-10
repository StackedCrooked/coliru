#include <iostream>

template<bool = true>
struct A {
    A() {
        static int x;
        std::cout << &x << "\n";
    }
};

static A<> a;