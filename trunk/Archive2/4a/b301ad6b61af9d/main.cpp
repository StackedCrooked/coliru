#include <iostream>

using std::cout;
using std::endl;

struct A
{
    A(int)    
    {
        cout << "A(int)" << endl;
    }
    
    A() : A(4)
    {
        cout << "A()" << endl;
    }
};

A a;

int main()
{
    
}