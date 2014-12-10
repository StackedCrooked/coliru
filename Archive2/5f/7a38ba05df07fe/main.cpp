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
        cout << endl << "func() of B";
    }
};

int main()
{
    A* ptr1 = new A;
    
    if (!dynamic_cast<B*>(ptr1))
        std::cout << "dynamic_cast failed";
}