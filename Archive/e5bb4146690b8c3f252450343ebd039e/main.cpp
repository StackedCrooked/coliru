#include <iostream>
#include <typeinfo>

template<int n> struct A {
    void operator()() {
        std::cout << n << '\n';
    }
};

template<std::nullptr_t> struct A {
    void operator()() {
        std::cout << "nullptr\n";
    }
};

int main() {
    A<42> a;
    A<nullptr> b;
    
    a();
    b();
}
