#include <iostream>

using std::cout;
using std::endl;

struct A
{
    A()
    {
        cout << "A()" << endl;
    }
};

struct B : A
{
    B() // A() will call
    {
        cout << "B()" << endl;
    }
};

B b;

int main()
{
    
}