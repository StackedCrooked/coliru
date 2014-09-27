#include <iostream>

struct X
{
    virtual void foo() = 0 { std::cout << "X::foo"; }
};

struct Y : X
{
    virtual void foo() override { X::foo(); }
};

int main()
{
    Y y;
    y.foo();
}