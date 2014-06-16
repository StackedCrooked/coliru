#include <iostream>

struct A {
    virtual void f() = 0;
};

void A::f() { std::cout << "ok\n"; }

struct B : A {
    virtual void f() override { A::f(); }
};

int main()
{
    B b;
    b.f();
}