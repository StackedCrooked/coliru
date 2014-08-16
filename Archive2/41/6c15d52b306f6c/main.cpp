#include <iostream>

using std::cout;
using std::endl;

struct A
{
    A(){ cout << "A()" << endl; }    
};

struct B : A 
{
    int A;
    int b;
    B(int b) : B::A::A()
    {
         B::b = b;
    }
};

B b(4);

int main()
{
    cout << b.b << endl;
}