#include <iostream>

struct A {
    A(int x) : x(x) { }
    int x;
};

struct B : public virtual A {
    B(int x) : A(x) { }
};

struct C : public virtual B {
    C(int x) : B(x) { }
};

struct D : public virtual C {
    D(int x) : C(x) { }
};

int main(int argc, char** argv) {
    D d(0);
    return 0;
}