#include <iostream>

using std::cout;
using std::endl;

struct S
{
    long l;
};

struct A
{
    int a;
};

struct B : A, S{ };

int main()
{
    cout << "sizeof(A) = " << sizeof(A) << endl;
    cout << "sizeof(S) = " << sizeof(S) << endl;
    cout << "sizeof(B) = " << sizeof(B) << endl;
}