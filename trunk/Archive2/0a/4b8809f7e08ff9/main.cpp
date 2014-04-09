#include <iostream>

using std::cout;
using std::endl;

struct A {
    void foo() && {
            cout << __PRETTY_FUNCTION__ << endl;
    }

    void foo() &  {
            cout << __PRETTY_FUNCTION__ << endl;
    }
};

int main() {
    A a;
    a.foo();

    A{}.foo();
}