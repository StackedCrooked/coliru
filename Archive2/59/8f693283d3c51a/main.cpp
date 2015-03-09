#include <iostream>

template<typename>
struct Base {
    virtual void foo() const {std::cout << "Base\n";}
};

struct Derived : Base<int> {
    void foo() const override {std::cout << "Derived\n";}  
};

int main() {
    Derived d;
    auto p = &d;
    p->template Base<int>::foo();
}