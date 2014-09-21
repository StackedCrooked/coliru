#include <iostream>

struct A {}; // complete type

template<class T> struct B;

template<class T>
struct D {
    static D s;
    D(B<D>&) {}
    friend void operator== (D const&, int) { std::cout << "hello!\n"; }
};
template<class T> D<T> D<T>::s;

template <class T>
struct B {};

int main() {
    B<D<A>> u;
    u == 42;
}