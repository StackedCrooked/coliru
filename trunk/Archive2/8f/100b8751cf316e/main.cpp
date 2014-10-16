#include <iostream>


#define print_address_of_vtable() std::cout << "vtable address: " << ((long*)this)[0] << std::endl



struct A
{
    A() { foo(); print_address_of_vtable(); }
    
    ~A() { foo(); print_address_of_vtable(); }
    
    virtual void foo()
    {
        std::cout << "A::foo()\n";
    }
};


struct B : A
{
    B() { foo(); print_address_of_vtable(); }
    
    ~B() { foo(); print_address_of_vtable(); }
    
    virtual void foo()
    {
        std::cout << "B::foo()\n";
    }
};


struct C : B
{
    C() { foo(); print_address_of_vtable(); }
    ~C() { foo(); print_address_of_vtable(); }
    
    virtual void foo()
    {
        std::cout << "C::foo()\n";
    }
};



int main()
{
    C c;
}
