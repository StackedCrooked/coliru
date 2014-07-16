#include <iostream>
#include <string>

class A {
typedef int I; // private member
I f();
friend I g(I);
static I x;
};

A::I A::f() { return 0; }
A::I g(A::I p = A::x);
A::I g(A::I p) { return 0; }
A::I A::x = 0;

int main(int argc, char** argv) {

  return 0;
}