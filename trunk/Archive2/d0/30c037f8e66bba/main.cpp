#include <iostream>

#include <type_traits>

struct S1 {
    void f() { std::cout << "S1::f\n"; }
};

struct S2 {
    void f() { std::cout << "S2::f\n"; }
    void g() { std::cout << "S2::g\n"; }
};

template <class T, class V = void>
struct D : private T {
    using T::f;
    //using T::g; // need this only if T provides g() function
};

template <class T>
struct D<T, decltype(void(&T::g))> : private T {
    using T::f;
    using T::g; // need this only if T provides g() function
};

int main() {
    D<S1>().f(); // ok. Prints 'S1::f'
    D<S2>().f(); // ok. Prints 'S2::f' 
    D<S2>().g(); // fail. But wants to be ok and prints 'S2::g'
    return 0;
}