#include <iostream>

struct X
{
    void x() { x(1); }
    virtual void x(int) { std::cout << "X\n"; }
    X()
    {
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

int main() {
    new Y;
    return 0;
}
