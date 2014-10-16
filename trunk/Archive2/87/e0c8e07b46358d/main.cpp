#include <iostream>



struct A
{
    A() { foo(); }
    
    ~A() { foo(); }
    
    virtual void foo()
    {
        std::cout << "A::foo()\n";
    }
};


struct B : A
{
    B() { foo(); }
    
    ~B() { foo(); }
    
    virtual void foo()
    {
        std::cout << "B::foo()\n";
    }
};


struct C : B
{
    C() { foo(); }
    ~C() { foo(); }
    
    virtual void foo()
    {
        std::cout << "C::foo()\n";
    }
};



int main()
{
    C c;
}
