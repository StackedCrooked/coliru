#include <iostream>

struct X
{
    virtual void x(int) { }
};

struct Y
{
    virtual void x(int const) { std::cout << "HA!"; }
};

int main()
{
    Y y;
    y.x(42);
}