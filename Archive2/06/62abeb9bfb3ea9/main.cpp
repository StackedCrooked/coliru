#include <array>
#include <iostream>
#include <typeinfo>
#include <vector>
#include <functional>
#include <chrono>
#include <cmath>
#include <exception>

using namespace std;
using namespace std::chrono;

struct C;

ostream& operator<<(ostream& out, const C& c) { cout << "(" << &c << ")"; return out; }

struct C {
    C() { cout << "c " << *this << endl; }
    C(const C&) { cout << "cc "<< *this << endl; }
    C(C&&) { cout << "mc " << *this<< endl; }
    ~C() { cout << "d " << *this<< endl; }
    C& operator=(const C&) { cout << "ca " << *this<< endl; return *this;}
    C& operator=(C&&) { cout << "ma "<< *this << endl; return *this; }
};

C foo() {
    C c;
    cout << "foo::c is " << c << endl;
    return c;
}

int main() {
    cout << "1 " << endl;
    C c = foo();
    cout << "main::c is " << c << endl;
    cout << "2 " << endl;
}
