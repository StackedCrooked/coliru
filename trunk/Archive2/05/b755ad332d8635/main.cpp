#include <iostream>
#include <typeinfo>

template<class T>
void f() {
    std::cout << typeid(T).name() << ", ";
}

template<class... ArgsT>
void g(ArgsT... args) {
    using swallow = char[];
    swallow { (f<ArgsT>(), '0')... };
}


int main() {
    g<int, double, char>(0,0.0,'0');
    //> int, double, char, 
}