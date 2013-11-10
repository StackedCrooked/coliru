#include <iostream>

template<typename T>
struct Z { };

namespace M {
    struct X { };

    template<typename T>
    void f(Z<T>) {
        std::cout << __PRETTY_FUNCTION__ << '\n';
    }
}

namespace N {
    template<typename T>
    struct Y { };

    template<typename T>
    void f(Z<T>) {
        std::cout << __PRETTY_FUNCTION__ << '\n';
    }
}

int main() {
    f(Z<N::Y<M::X>>());
}
