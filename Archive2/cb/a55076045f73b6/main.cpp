#include <iostream>

using namespace std;


void f()
{
    cout << "global f" << endl;
}

struct A
{
    void f()
    {
        cout << "A's f" << endl;
    }
};

struct B : A
{
    B()
    {
        f(); // A::f() is always called, and ::f is always ignored
        ::f();
    }
};

int main()
{
    B();
}