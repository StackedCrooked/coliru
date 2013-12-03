#include <iostream>

struct A {
    virtual A *make() = 0;
    virtual void print() {
        std::cout << "I'm an A" << std::endl;   
    }
};

struct B : public A {
    B *make() override {
        return new B{};  
    }
    void print() override {
        std::cout << "I'm a B" << std::endl;   
    }
};

int main() {
    B some_b;
    A &a = some_b;
    A *another_b  = a.make();
    another_b->print();
    return 0;
}