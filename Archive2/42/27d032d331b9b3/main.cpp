#include <iostream>
#include <typeinfo>
#include <cassert>

using std::cout;
using std::endl;

long unsigned int hash_in_constructor;

struct A
{
    virtual void foo()
    {
        cout << "A" << endl;
    }
    
    A()
    { 
        hash_in_constructor = typeid(this).hash_code();
    }
};


int main()
{
    cout << hash_in_constructor << endl;
    cout << typeid(A).hash_code();
}