#include <iostream>

struct Base {
    Base() {}
    virtual ~Base() {}
    virtual void foo() const = 0;
};

template<typename Derived>
struct Base_CRTP : Base {
    Base_CRTP() { static_cast<Derived*>(this)->Derived::foo(); }
    virtual ~Base_CRTP() {}
    virtual void foo() const = 0;
};

struct Derived : Base_CRTP<Derived> {
    Derived() {}
    void foo() const { std::cout << "Hello from Derived!" << std::endl; }
};

int main() {
    Base* b = new Derived();
    delete b;
}