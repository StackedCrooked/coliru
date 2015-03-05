#include <iostream>

using std::cout;
using std::endl;

struct A
{
    int i;
    A(int i) : i(i) { cout << "A(int) i = " << i << endl; }
};

struct B : virtual A
{
    B() : A(1) { cout << "B() i = " << i << endl; }
};

struct C : B
{
    C() : A(10), B() { cout << "C() i = " << i << endl; }
};


int main()
{
    B b;
    cout << b.i << endl;
    C c;
    cout << c.i << endl;
}
