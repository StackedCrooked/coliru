#include <iostream>
using namespace std;

int main()
{
    int x = 0;

    struct A 
    {
        // meaningful members
        int y;
        int f() { return x + y; };

        // free variables
        int & x;

        // Constructor
        A(
            // meaningful arguments
            int y,

            // capturing free variables
            int & x

        ) : y(y), x(x) {}
    };

    A a1(1, x);
    A a2(2, x);

    cout << a1.f() << endl; // prints 1
    cout << a2.f() << endl; // prints 2

    x = 2;
    cout << a1.f() << endl; // prints 3
    cout << a2.f() << endl; // prints 4
}