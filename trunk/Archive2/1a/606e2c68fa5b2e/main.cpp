#include <iostream>

struct A {
    A(int) { }
};

struct B : public virtual A {
    B(int) : A(0) { }
};

struct C : public virtual B {
    C() : B(0) { }
};

int main(int argc, char** argv) {
    C c;
    return 0;
}