
#include <iostream>

struct B
{
    virtual void f() {std::cout << "B::f" << std::endl;}
};

struct D : B
{
    void f()
    {
        std::cout << "D::f" << std::endl;
    }
    void g()
    {
        B:f();
    }
};

int main()
{
    D d;
    d.g();
}