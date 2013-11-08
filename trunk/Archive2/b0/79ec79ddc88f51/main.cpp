#include <iostream>
using namespace std;

int main()
{
    int x = 0;

    struct A 
    {
        int y;
        A(int y) : y(y) {}

        int f() { return x + y; };
    };

    A a1(1);
    A a2(2);

    cout << a1.f() << endl; // would print 1
    cout << a2.f() << endl; // would print 2

    x = 2;
    cout << a1.f() << endl; // would print 3
    cout << a2.f() << endl; // would print 4
}