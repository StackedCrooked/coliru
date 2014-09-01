#include <iostream>
#include <typeinfo>

using std::cout;
using std::endl;

struct A
{
    ~A()
    {
        cout << "~A" << endl;
    }
    
    A()
    { 
        cout << "A()" << endl;
    }
};

A *a = new A;


int main()
{
    a -> ~A(); //Does lifetime of *b end?
}