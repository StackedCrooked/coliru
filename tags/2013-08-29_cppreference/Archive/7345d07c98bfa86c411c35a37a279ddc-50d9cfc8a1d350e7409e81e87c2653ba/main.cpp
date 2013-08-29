struct A {
    template <typename T> struct B {
        template <typename U> void foo(U arg);
    };
};

template <typename T>
template <typename U>
void
A::B<T>::foo(U arg) {}

#include <iostream>
int main() {
    A::B<int> b;
    b.foo(3);
    std::cout << "pass";
}