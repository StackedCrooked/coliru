#include <iostream>

struct A
{
    int i;
    virtual void me()
    {
        std::cout << this << '\n';
    }
};

struct B : public A
{
    int j;
    void me()
    {
        std::cout << this << '\n';
    }
};

int main()
{
    B o;
    o.me();
    A *a = &o;
    a->me();
}
