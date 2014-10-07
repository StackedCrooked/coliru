#include <iostream>

struct X
{
    void x() { x(1); }
    virtual void x(int) { std::cout << "X\n"; }
    X()
    {
        X::x();
    }
};

struct Y : public X
{
    void x(int) { std::cout << "Y\n"; }
    Y(): X()
    {
        X::x();
    }
};

struct Z : public Y
{
    void x(int) { std::cout << "Z\n"; }
    Z()
    {
        X::x();
    }
};

int main() {
    Z z;
    return 0;
}
