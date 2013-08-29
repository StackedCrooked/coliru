#include <iostream>

struct A
{
    virtual int operator & ( A & ) { return 0; }
};

struct B : public A {};
struct C : public A {};

struct D : public C, public B {};

int main()
{
    D d;
    std::cout << &d << std::endl;
    return 0;
}