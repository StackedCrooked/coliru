#include <iostream>

class B {
public:
    void print() { std::cout << "Base\n"; }
};

class D : public B {
public:
    void print() { std::cout << "Derived\n"; }
};

int main() {
    D d;
    d.print();
    d.B::print();

    return 0;
}