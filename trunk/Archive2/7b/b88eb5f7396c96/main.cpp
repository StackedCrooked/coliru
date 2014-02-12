#include <iostream>

struct A 
{ 
    int x;
};

class B : public A
{
    int y;
};

struct C : private B
{
    using A::x;
    operator A* () { return this; }
};

int main()
{
    C c;
    A* x = c; // OK
    //B* y = c; // ERROR!
}