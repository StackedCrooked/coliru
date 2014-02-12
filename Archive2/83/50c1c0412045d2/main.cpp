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
};

int main()
{
    C c;
    c.x; // OK
    //c.y; // ERROR!
}