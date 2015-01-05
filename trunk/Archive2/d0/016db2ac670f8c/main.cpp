#include <iostream>

template<typename T>
class A;

template<typename T, typename U>
A<T> makeA(const U & u) {
    (void) u;
    std::cout << "makeA";
    return A<T>();
}


template<typename T>
class A {
    
    A() {}
    
    friend A<T> makeA<T, double>(const double&);
};


int main() {
    makeA<double, double>(3);
    return 0;
}