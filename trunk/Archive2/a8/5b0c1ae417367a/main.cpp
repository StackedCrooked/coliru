#include <iostream>
 
template<class T> struct Specialized;   //   : std::false_type {};
//template<>        struct Specialized<int> : std::true_type  {};
 
template<class T> void f(T& t) noexcept(Specialized<T>::value);
template<class T> void f(T* t) noexcept(noexcept(f(*t)));
 
int main() {
    int x, *y, **z;
 
    std::cout << noexcept(f(z)) << "\n";
}