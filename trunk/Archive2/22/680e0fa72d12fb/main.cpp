#include <iostream>

using std::cout;
using std::endl;

struct A
{
    virtual void foo(){ };
    
    A()
    {
        cout << "A()" << endl;
    }
};

struct B : virtual A
{
    virtual void bar() = 0;
    
    B()
    {
        cout << "B()" << endl;
    }
};

struct C : B
{
    void bar(){ };
    C() : B()
    {
        cout << "C()" << endl;
    }
};

C c;

int main()
{
    
}