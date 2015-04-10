#include <iostream>

template<typename T>
struct Base {
    void foo() {std::cout << "Base::foo";}
};

void foo() {std::cout << "::foo";}

template<typename T>
struct Derived : Base<T> {
    void bar() {
        foo();
    }
};

int main() {
    Derived<int> d;
    d.bar();
}