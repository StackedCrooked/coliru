#include <iostream>

using namespace std;

class A {
public:
    A(int) {
        cout << "Base class" << endl;
    }
};

class B : virtual public A {
public:
    virtual void do_something() = 0;
};

class C : public B {
public:
    C()
        : A(1) {
        cout << "C class" << endl;
    }

    virtual void do_something() {
    }
};

int main() {}