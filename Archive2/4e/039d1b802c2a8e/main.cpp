#include <iostream>

struct A
{
    virtual ~A() = default;
};

struct B
{
    virtual ~B() = default;
};

struct C : A, B
{
    virtual ~C() = default;
};

int main()
{
    C c;
    A* ap = &c;
    B* bp = dynamic_cast<B*>(ap);
    
    std::cout << std::boolalpha << (bp != nullptr) << std::endl;
}