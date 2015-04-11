#include <iostream>

struct A {A() {std::cout << "::A\n";} };

namespace N {
    struct A {
        A() {std::cout << "N::A\n";}
        void g() { }
        template <class T> operator T() {return {};}
    };
}

int main() {
    N::A a;
    a.operator A(); // calls N::A::operator N::A
}