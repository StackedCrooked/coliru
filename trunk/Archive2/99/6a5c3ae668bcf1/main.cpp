#include <iostream>

class A {
public:
    virtual void f() = 0;
};

void A::f() {
    std::cout << "...\n";
}

int main() {
    A a;
}