#include <iostream>
#include <typeinfo>

using std::cout;
using std::endl;

struct C;

struct B
{
    int a;
    B *b;
    B(C *c);
};

struct C : B
{
    C() : B(this)
    {
        cout << "C()" << endl;
    }
};

B::B(C *c)
{
    a = 5;
    b= dynamic_cast<B*>(c); //1, UB?
}

C c;
int main()
{
    cout << c.b -> a << endl;
    cout << c.a << endl;
}