#include <iostream>
using namespace std;
class A
{
public:
    A(){ cout << "A ctor" <<endl;}
    A(const A & a){cout << "A copy ctor" <<endl;}
    A & operator = (const A & a){cout << "A assignment" <<endl; return *this;}
    ~A(){cout << "A dtor" <<endl;}
};

A func()
{
    A a1;
    return a1;
}

int main()
{
    A a2 = func();
    return 0;
}