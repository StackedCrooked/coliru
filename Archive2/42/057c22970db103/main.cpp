#include <iostream>

struct A {
    void foo() {}
};

struct B : public A {
    using A::foo;
};

template<typename U, U> struct helper{};

int main() {
    helper<decltype(&A::foo), &A::foo> compiles;
    helper<decltype(&B::foo), &B::foo> also_compiles;
}
