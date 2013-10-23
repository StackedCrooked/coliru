#include <iostream>
#include <typeinfo>
using namespace std;

class Base {
    public:
        virtual void do_it() = 0;
        virtual ~Base() {}
};

struct Derived1 : public Base {
    void do_it() { cout << " ... do this\n"; }
};
struct Derived2 : public Base {
    void do_it() { cout << " ... do that\n"; }
};

void f(Base &r) {
    r.do_it();
}

int main() {
    Derived1 d1;
    Derived2 d2;
    bool b = false;
    if (b) f(d1); else f(d2);
}
