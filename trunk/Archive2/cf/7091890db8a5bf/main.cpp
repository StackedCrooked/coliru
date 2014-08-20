#include <iostream>

struct A
{
    virtual std::string GetFunnyName() const
    {
        return "AaAaA";
    }
};

struct B : A
{
    virtual std::string GetFunnyName() const
    {
        return "bBbBb";
    }
};

int main()
{
    A* a = new A();
    A* b = new B();
    
    std::cout
        << a->GetFunnyName() << std::endl
        << b->GetFunnyName() << std::endl;
}