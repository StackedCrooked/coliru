#include <iostream>

class Base
{
public:
    virtual Base* foo() { std::cout << "Base::foo() \n"; return this; }
};

class Derived : public Base
{
public:
    virtual Derived* foo() { std::cout << "Derived::foo() \n"; return this; }
};

int main()
{
    Base* instance = new Derived;
    instance->foo();
}
