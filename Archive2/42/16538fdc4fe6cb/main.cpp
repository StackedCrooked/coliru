#include <iostream>
#include <memory>
#include "boost/variant.hpp"

struct Derived1 {
    void foo(){
        std::cout << "D1" << std::endl;
    }
};

struct Derived2 {
    void foo(){
        std::cout << "D2" << std::endl;
    }
};

template<class Type>
void func(Type& x) {
    x.foo();
}

int main() {
    Derived1 d1;
    Derived2 d2;
    func(d1);
    func(d2);
}