#include <iostream>

struct A {}; // complete type

template<class T> struct B;

namespace N
{
    template<class T>
    struct D {
        D(B<D>&) {}
        friend void operator== (D const&, int) { std::cout << "hello!\n"; }
    };
}

template <class T>
struct B {};

int main() {
    B<N::D<A>> u;
    u == 42;
}