#include <iostream>
using namespace std;

class Base {
public:
    Base() { cout << "Base constructed" << endl; }
    virtual void m() = 0;
    virtual ~Base() = 0;
};
void Base::m() { cout << "Base::m" << endl; } // default implementation
Base::~Base() { cout << "Base destructed" << endl; }

class Derived : public Base {
    char *cp;
public:
    Derived() : cp(new char[100]) { cout << "memory allocated" << endl; }
    void m() { Base::m(); } // make it explicit you want the default
    virtual ~Derived() { delete[] cp; cout << "memory freed" << endl; }
};


int main() {
    cout << "main started" << endl;
    Base *p = new Derived();
    p->m();
    delete p;
    cout << "main ending" << endl;
}   
