#include <iostream>

using std::cout;
using std::endl;

struct A
{
    virtual void foo()
    {
        cout << "A" << endl;
    }
    
    A(){ }
};

struct B : A
{
    virtual void foo()
    {
        cout << "B" << endl;
    }
    
    B()
    {
        foo();
    }  
};

struct C : B
{
    virtual void foo()
    {
        cout << "C" << endl;
    }
    
    C() : B(){ }      
};

C c;

int main()
{
    c.foo();
    C::C();
}