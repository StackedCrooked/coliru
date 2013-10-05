#include <iostream>
#include <string>
#include <vector>

class Base
{
    public:
    virtual void PureVirtualFunction() = 0;
    virtual void VirtualFunction1()
    {
        std::cout << "Base::VirtualFunction()" << std::endl;
    }
    void NonVirtualFunction()
    {
        std::cout << "Base::NonVirtualFunction()" << std::endl;
    }
};

class Derived : public Base
{
    public:
    virtual void PureVirtualFunction()
    {
        std::cout << "Derived::PureVirtualFunction()" << std::endl;
    }
    virtual void VirtualFunction1()
    {
        std::cout << "Derived::VirtualFunction()" << std::endl;
    }
    void NonVirtualFunction()
    {
        std::cout << "Derived::NonVirtualFunction()" << std::endl;
    }
};

int main()
{
    Derived* derived = new Derived;
    derived->PureVirtualFunction();
    derived->VirtualFunction();
    derived->NonVirtualFunction();
    
    Base* base = static_cast<Base*>(derived);
    base->PureVirtualFunction();
    base->VirtualFunction();
    base->NonVirtualFunction();
}
