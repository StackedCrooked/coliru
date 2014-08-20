#include <iostream>

using std::cout;
using std::endl;

struct A
{
    virtual void foo(){ };
    
    A(int)
    {
        cout << "A(int)" << endl;
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
    C() : A(10), B()
    {
        cout << "C()" << endl;
    }
};

C c;

int main()
{
    
}