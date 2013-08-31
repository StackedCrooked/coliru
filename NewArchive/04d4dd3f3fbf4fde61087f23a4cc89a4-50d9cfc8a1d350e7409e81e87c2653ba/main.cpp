#include <iostream>

using namespace std;

struct A
{
    A(int) { cout << "A(int)" << endl; }
};

struct B
{
    B(A) { cout << "B(A)" << endl; }    
};

struct C
{
    C(B) { cout << "C(B)" << endl; }
    C(const C&) { cout << "C(const C&)" << endl; }
};

int main()
{
    C c1{{{1}}};
    C c2{c1};
    C c3{{c2}};
}
