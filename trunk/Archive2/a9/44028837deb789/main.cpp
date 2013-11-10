#include <iostream>

namespace M {
    struct X { };

    void f(X) {
        std::cout << __PRETTY_FUNCTION__ << '\n';
    }
}

namespace N {
    template<typename T>
    struct Y { };

    template<typename T>
    void f(Y<T>) {
        std::cout << __PRETTY_FUNCTION__ << '\n';
    }
}

template<typename T>
struct Z { };

int main() {
    f(Z<N::Y<M::X>>());
}
