

#include <iostream>

struct Base
{
    Base() { foo(); }

    virtual void foo() = 0;
};

void Base::foo()
{
    std::cout << "Hello!";
}

struct Derived : Base
{
    void foo() override { std::cout << "World!"; }
};

int main()
{
    Derived d; // Prints "Hello!". Not undefined behaviour.
}

