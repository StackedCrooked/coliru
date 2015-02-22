#include <iostream>
#include <string>

struct B;


struct A {
    B * b;
};

struct B {
    A * a;
};


int main() {
    A a;
    B b;
    a.b = &b;
    b.a = &a;
}
