#include <iostream>
#include <typeinfo>
using namespace std;

class Base {
    public:
    virtual ~Base() {}
};

class Derived1 : public Base {};
class Derived2 : public Base {};

void f(Base &r) {
    if (typeid(r) == typeid(Derived1))
        cout << " ... do this\n";
    else if (typeid(r) == typeid(Derived2))
        cout << " ... do that\n";
    else 
        cout << "how that ?!?\n";
}

int main() {
    Derived1 d1;
    Derived2 d2;
    bool b = true;
    if (b) f(d1); else f(d2);
}
