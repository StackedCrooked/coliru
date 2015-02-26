#include <iostream>

template<class T> struct Specialized : std::false_type {};
template<> struct Specialized<int> : std::true_type {};

template<class T>                void f(T& a)      noexcept(Specialized<T>::value);
template<class T, std::size_t N> void f(T (&a)[N]) noexcept(noexcept(f(*a)));

int main() {
    int x;
    int y[1];
    int z[1][1];
    
    std::cout << noexcept(f(x)) << "\n";
    std::cout << noexcept(f(y)) << "\n";
    std::cout << noexcept(f(z)) << "\n";
}