#include <iostream>

class Foo
{
public:
    virtual void f(int) {
        std::cout << "Foo::f" << std::endl;
    }
};


class Bar : public Foo
{
public:
    void f(short) {
        std::cout << "Bar::f" << std::endl;
    }
};

int main()
{
    Bar b;

    Foo *x = &b;
    x->f(5);
}