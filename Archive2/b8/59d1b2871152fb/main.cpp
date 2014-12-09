#include <iostream>
#include <memory>
#include "boost/variant.hpp"

struct Base {
    virtual void foo() = 0;
};

struct Derived1 : public Base {
    virtual void foo() {
        std::cout << "D1" << std::endl;
    }
};

struct Derived2 : public Base {
    virtual void foo() {
        std::cout << "D2" << std::endl;
    }
};

int main() {
    bool condition = false;
    std::unique_ptr<Base> x = condition ? std::unique_ptr<Base>(new Derived1()) : std::unique_ptr<Base>(new Derived2());
    x->foo();
}