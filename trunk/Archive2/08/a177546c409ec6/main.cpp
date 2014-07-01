
#include <iostream>
using namespace std;
class A {
    int i;
public:
    A(int i) : i(i) { cout << i << endl; }
    A(const A &o) : i(o.i) { cout << i << endl; }
    ~A() { cout << i << endl; }
    friend A f(const A &, A, A *);
};
A f(const A &a, A b, A *c) { return *c; }
int main() { 
    f(1, A(2), &A(3));
}