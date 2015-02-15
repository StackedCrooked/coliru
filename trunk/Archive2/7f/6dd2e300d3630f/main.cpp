#include <iostream>

struct V {
    V(int i) {
        std::cout << "initialized v" << '\n';
    }
};

struct A {
    A() {
        std::cout << "initialized a" << '\n';
    }
};

struct B : virtual V, virtual A {
    B(int i) :V{i} {
        std::cout << "initialized b" << '\n';
    }
};

class C : virtual V, virtual A {
public:
    C(int i) : V{i} {
        std::cout << "initialized c" << '\n';
    }
};

class D : virtual public B, virtual public C {
public:
    D(int i, int j) :V{i}, B{i}, C{j} {
        std::cout << "initialized d" << '\n';
    }
};

int main() {
    D* d = new D{3,3}; //ok
    B* b = new D{3,3}; //ok
    C* c = new D{3,3}; //undefined
    delete d;
    delete b;
    delete c;

}