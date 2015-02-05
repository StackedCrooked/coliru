#include <iostream>
#include <typeinfo>

struct Base {
    virtual void Teste();
};

struct Derived : Base { };

void Base::Teste() {
    Base *a = this;
    Base *b = dynamic_cast<Derived *>(this);

    if (a)
        std::cout << typeid(*a).name() << std::endl;
    if (b)
        std::cout << typeid(*b).name() << std::endl;
}

int main() {
    Derived d;
    d.Teste();

    Base b;
    b.Teste();

    return 0;
}