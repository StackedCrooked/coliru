
#include <iostream>

using namespace std;

void f(int i, float f) { cout << 'A' << endl; }

void f(float f, double d) { cout << 'B' << endl; }

void f(char c, int a) { cout << 'C' << endl; }

struct A
{
    A(A& a) {}
};

int main() {

/*
    f(0, 0u); // (1)
    f(0.5f, 3l); // (2)
    f('c', 27); // (3)
    f('z', 3.5); // (4)
*/

}