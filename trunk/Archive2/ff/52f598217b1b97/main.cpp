#include <iostream>

using std::cout;
using std::endl;

struct A
{
    int foo();
    
    int a = 4;
};

int A::foo()
{
    cout << "foo()" << endl;
    return 1;
}

int A::a = 4;

A a;

int main()
{
    a.foo();
    cout << a.a << endl;
}