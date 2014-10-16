#include <iostream>


#define TRACE() \
    std::cout << __FUNCTION__ << " this=" << this << " static_cast<A*>(this)=" << static_cast<A*>(this) << " vtable address: " << (static_cast<long*>(static_cast<void*>(static_cast<A*>(this))))[0] << std::endl;



struct A
{
    A() { foo(); TRACE(); }
    
    ~A() { foo(); TRACE(); }
    
    virtual void foo()
    {
        std::cout << "A::foo() ";
    }
};


struct B : A
{
    B() { foo(); TRACE(); }
    
    ~B() { foo(); TRACE(); }
    
    virtual void foo()
    {
        std::cout << "B::foo() ";
    }
};


struct C : B
{
    C() { foo(); TRACE(); }
    ~C() { foo(); TRACE(); }
    
    virtual void foo()
    {
        std::cout << "C::foo() ";
    }
};



int main()
{
    C c;
}
