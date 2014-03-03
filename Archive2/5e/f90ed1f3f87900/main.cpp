#include <iostream>
#include <stdexcept>

class A {
public:
    A() { std::cout << "A::A()" << std::endl; }
    ~A() { std::cout << "A::~A()" << std::endl; }
};

class B {
public:
    B() {
        std::cout << "B::B()" << std::endl;
        throw std::logic_error("oops");
    }
private:
    A m;
};

int main() {
    B b;
}
