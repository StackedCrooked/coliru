#include <iostream>
#include <complex>
using namespace std;
class Base
{
public:
    virtual void f(int);
    virtual void f(double);
    virtual ~Base() {};
};

void Base::f(int) { cout << "Base::f(int)" << endl; }
void Base::f( double ) { cout << "Base::f(double)" << endl; }

class Derived: public Base {
public:
    void f(complex<double>);
};

void Derived::f(complex<double>) { cout << "Derived::f(complex)" << endl; }

int main()
{
    Base b;
    Base* pb = new Derived;
    pb->f(1.0);
    delete pb;
}