#include <iostream>
#include <string>

struct B;

B * newb();

struct A {
    B * b = newb();
};

struct B {
    A * a = new A;
};

B * newb() {
    return new B;
}

int main() {
    A a;
}
