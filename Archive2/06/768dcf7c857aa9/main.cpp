#include <iostream>

struct X
{
    virtual void foo() = 0;
};

struct Y : X
{
    virtual void foo() override { X::foo(); }
};

void X::foo() { std::cout << "X::foo"; }

int main()
{
    Y y;
    y.foo();
}