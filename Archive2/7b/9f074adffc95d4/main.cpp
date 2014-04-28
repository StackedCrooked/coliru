#include <iostream>

template <template <typename> class>
struct X {
        X() { std::cout << "1"; }
};

template <typename>
struct Y {};

template <typename T>
using Z = Y<T>;

template <>
struct X<Y> {
        X() { std::cout << "2"; }
};
int main() {
        X<Y> x1;
        X<Z> x2;
}
