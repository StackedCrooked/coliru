#include <iostream>
using namespace std;

class A {
public:
    A() { cout << "A()" << endl; }
    ~A() { cout << "~A()" << endl; }
};

void f_noexcept() noexcept {
    A a;
    throw 1;
}

void f_emptythrow() throw() {
    A a;
    throw 1;
}

int main() {
    f_noexcept();
//        f_emptythrow();
}
