#include <iostream>

struct A {
    virtual void lol() = 0;
};

struct B : A {
    virtual void lol() {
        std::cout << "B::lol()\n";
    }
};

struct C : B {};

int main() {
    C c;
    c.lol();
}