#include <iostream>
#include <typeinfo>

template<class T>
void f() {
    std::cout << typeid(T).name() << ", ";
}

template<class... ArgsT>
void g(ArgsT... args) {
    f<args>()...;
}


int main() {
    g<int, double, char>();
    //> int, double, char, 
}