#include <iostream>


using namespace std;


class X
{
public:
    static int def_arg;
    void f(int e= def_arg);
};

int X::def_arg = 7;

inline void X::f(int e)
{
    cout << e << endl;
}

void g(X& a)
{
    a.f(); // maybe f(7)
    a.def_arg = 9;
    a.f(); // f(9)
}

int main()
{
    X a;

    g(a);

}