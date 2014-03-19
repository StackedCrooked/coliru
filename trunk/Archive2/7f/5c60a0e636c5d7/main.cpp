#include <iostream>

class Base
{
public:
    void testy() { test(); }
    virtual void test() { std::cout << "Base" << std::endl; }
};

class Derived : public Base
{
public:
    void test() override { std::cout << "Derived" << std::endl; }
};

int main()
{
    Derived d;
    Base& b = d;
    d.testy();
    b.testy();
}