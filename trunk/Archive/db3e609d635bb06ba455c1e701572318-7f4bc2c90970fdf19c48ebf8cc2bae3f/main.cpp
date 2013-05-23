#include <iostream>

class Base
{
public:
    virtual ~Base()
    {
        
    }
    
    virtual void method()
    {
        std::cout << "Base" << std::endl;
    }
};

class Derived: public Base
{
public:
    void method(int) override
    {
        std::cout << "Derived" << std::endl;
    }
};

int main()
{
    Derived* d = new Derived;
    Base* b = d;
    
    d -> method();
    b -> method();
    
    delete d;
}
    