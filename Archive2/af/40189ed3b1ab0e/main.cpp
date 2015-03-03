#include <iostream>

using std::cout;
using std::endl;

struct A
{
    // N.B.: no default ctor
    A(int)
    {
        cout << "A(int)" << endl;
    }
};

struct B : virtual A
{
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