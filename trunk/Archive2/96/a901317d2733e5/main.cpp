#include <iostream>
#include <type_traits>

struct S1 {
    void f() { std::cout << "S1::f\n"; }
};

struct S2 {
    void f() { std::cout << "S2::f\n"; }
    void g() { std::cout << "S2::g\n"; }
};

struct S3 {
    void g() { std::cout << "S3::g\n"; }
};

template <class T, class = void>
struct D_f {};

template <class T>
struct D_f<T, decltype(void(&T::f))> : private virtual T {
    using T::f;
};

template <class T, class = void>
struct D_g {};

template <class T>
struct D_g<T, decltype(void(&T::g))> : private virtual T {
    using T::g;
};

template <class T>
struct D : D_f<T>, D_g<T> {
};


int main() {
    D<S1>().f();
    D<S2>().f();
    D<S2>().g();
    D<S3>().g();
    return 0;
}