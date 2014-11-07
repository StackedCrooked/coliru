#include <iostream>

template<class T> struct Specialized      : std::false_type {};
template<>        struct Specialized<int> : std::true_type  {};

template<class T>                void f(T& a) noexcept(Specialized<T>::value);
template<class T, std::size_t N> void f(T (&a)[N]) noexcept(noexcept(f(*a)));

int main(int argc, char** argv) {
    int x, y[1], z[1][1];

    std::cout << noexcept(f(x)) << "\n"
              << noexcept(f(y)) << "\n"
              << noexcept(f(z)) << "\n";
}