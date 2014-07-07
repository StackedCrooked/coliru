#include <iostream>
#include <utility>

template <typename T>
struct Foo {
    T Bar;
    Foo(const T& a) : Bar(a) {
        std::cout
            << "Default constructor called."
        << std::endl;
    }
    Foo(const Foo<T>& a) : Bar(a.Bar) {
        std::cout
            << "Copy constructor called."
        << std::endl;
    }
    Foo(Foo<T>&& a) : Bar(a.Bar){
        std::cout
            << "Move constructor called."
        << std::endl;
    }
};

template <typename T>
Foo<T> Baz(const T& Quux) {
    return Foo<T>(Quux);
}

int main() {
    Foo<int> A = Baz(10);
    Foo<int> B = (Foo<int>&&)A;
    Foo<int> C = std::move(B);
    std::cout << A.Bar << std::endl;
}