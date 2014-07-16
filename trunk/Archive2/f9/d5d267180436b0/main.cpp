#include <iostream>

class Base
{
public:
    Base(){}

    Base operator=(Base ob2)
    {
        std::cout << "Using Base operator=() " << '\n';
        return *this;
    }
};

class Derived : public Base
{
public:
    Derived(){}
    Derived operator=(Base ob2)
    {
        std::cout << "Using Derived operator=() " << '\n';
        return *this;
    }
};

int main()
{
    Derived derived1, derived2;
    Base base1;

    derived1 = derived2;  // Uses base operator=()

    derived1 = base1;  // Uses derived operator=()

    return 0;
}