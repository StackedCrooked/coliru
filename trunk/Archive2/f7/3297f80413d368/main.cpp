#include <iostream>

using std::cout;
using std::endl;

struct A
{
    int i;
    // N.B.: no default ctor
    A(int i) : i(i)
    {
        cout << "A(int)" << endl;
    }
};

struct B : virtual A
{
    B():A(10000000)
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
    std::cout << c.i << '\n';

}