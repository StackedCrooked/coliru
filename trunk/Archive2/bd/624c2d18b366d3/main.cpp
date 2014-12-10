#include <iostream>
#include <typeinfo>
using namespace std;

class A
{
    virtual void dummy() {};
    void f()
    {
        cout << endl << "A f()";
    }
};

class B
{
public:
    void func()
    {
        int i;
        cout << endl << "func() of B";
    }
};

int main()
{
    A* ptr1;
    B* ptr2;
    ptr1 = new A;
    ptr2 = dynamic_cast<B*>(ptr1);
    if (ptr2 == NULL)
        cout << endl << "dynamicastfailed";
    cout << endl << "Type=" << typeid(ptr2).name();
    ptr2->func();
}