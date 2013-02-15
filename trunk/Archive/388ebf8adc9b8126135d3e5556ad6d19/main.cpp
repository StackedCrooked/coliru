#include <iostream>

struct Base {
    void foo() {std::cout << "base foo\n";}
    virtual void bar() {std::cout << "base bar\n";}
};

struct Derived : Base {
    void foo() {std::cout << "derived foo\n";}    
    void bar() {std::cout << "derived bar\n";}
};

int main() {
    Base *b = new Derived();
    b->foo();
    b->bar();
}