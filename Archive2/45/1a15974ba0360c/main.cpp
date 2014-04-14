#include <iostream>
using namespace std;

struct A {
    virtual ~A() { cout << "~A" << endl; }
    virtual void doit() const = 0;
};

struct B : public A
{
    ~B() override { cout << "~B" << endl; }
    void doit() const override { cout << "A::doit" << endl; }
};

struct C : public A
{
    ~C() override { cout << "~C" << endl; }
    virtual void doit() const { cout << "C::doit" << endl; }
};

void foo(bool p)
{
    cout << "foo( " << p << ")" << endl;
    const A &a = (p ? static_cast<const A &>(B()) : static_cast<const A &>(C()));
    a.doit();
}

auto main( int argc, char* argv[] ) -> int
{
    cout << boolalpha;

    foo( true );
    cout << endl;
    foo( false );
}
