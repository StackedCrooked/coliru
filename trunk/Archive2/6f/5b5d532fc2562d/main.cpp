#include <iostream>

using namespace std;

class Base {
public:
    virtual~Base() {}
    virtual void Foo() = 0;
}; // class Base

void Base::Foo() {cout << "Base::Foo" << endl;}

class Derived : public Base {
public:
    virtual~Derived() {}
    virtual void Foo() {cout << "Derived::Foo" << endl;}
    void ParentFoo() {Base::Foo();}
}; // class Derived

int main()
{
    Derived *d = new Derived();
    d->Foo();
    d->ParentFoo();
    delete d;
    return 0;
}
