template<typename T>
struct has_x {
    template<typename U>
    static char (&check(int))[1 + sizeof(&U::x)];
    template<typename>
    static char (&check(...))[1];

    static const bool value = sizeof(check<T>(0)) != 1;
};

#include <iostream>

struct A { int x; };
struct B { const char x; };
struct C { void x() volatile ; };
struct D : A { };
struct E {};
struct F : A, B {};

int main()
{
    std::cout
        << has_x<A>::value
        << has_x<const B>::value
        << has_x<volatile C>::value
        << has_x<const volatile D>::value
        << has_x<E>::value
        << has_x<F>::value;
}
