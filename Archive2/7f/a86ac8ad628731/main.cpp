#include <memory>
#include <iostream>

class Base {
public:
    virtual void funcX() {}
};

class Derived1 : public Base {
public:
    void funcA() {  std::cout << "called derived1\n"; }
};

class Derived2 : public Base {
public:
    void funcB() {  std::cout << "called derived2\n"; }
};

void func(Base* x) {
    Derived1* one = dynamic_cast<Derived1*>(x);
    Derived2* two = dynamic_cast<Derived2*>(x);
    if (one) {
        // `x` was a `Derived1`
        one->funcA();
    } else {
        // `x` was a `Derived2`
        two->funcB();
    }
}

int main() {
    std::unique_ptr<Base> pointer1(new Derived1());
    std::unique_ptr<Base> pointer2(new Derived2());
    func(pointer1.get());
    func(pointer2.get());
    return 0;
}