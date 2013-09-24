#include <iostream>

class B { int x; public: void add() { x++; } void output() { std::cout << x << '\n'; } };
class A { B b; public: void alternateB() { b.add(); } void output() { b.output(); } };

int main () {
    A a;
    a.output();
    a.alternateB();
    a.output();
    a.alternateB();
    a.output();
    a.alternateB();
    a.output();
}