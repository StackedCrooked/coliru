#include <iostream>
using namespace std;

struct A {
    A() { cout << "A" << endl; }
    A(int a) { cout << "Aplus" << endl; }
};

struct B : virtual public A {
    B() : A(1) { cout << "B" << endl; }
};

struct C : public A {
   C() : A(1) { cout << "C" << endl; }
};

struct D : virtual public A {
    D() : A() { cout << "D" << endl; }
};

struct E : public B, virtual public C, public D {
    E() { cout << "E" << endl; }    
};

struct F :public D, virtual public C {
    F() { cout << "F" << endl; }
};
struct G : public E, public F {
    G() { cout << "G" << endl; }    
};

int main() {
    G a;
    return 0;
}