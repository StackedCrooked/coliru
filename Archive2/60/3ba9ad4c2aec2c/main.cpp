#include <iostream>
#include <utility>

struct A {
    template<typename... Args>
    A(Args&&... args) : A({ std::forward<Args>(args)... }) { }

    int a, b, c;
};

int main() {
    A x(1, 2, 3);
    std::cout << x.a << x.b << x.c << '\n';
}

