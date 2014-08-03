#include <iostream>
#include <complex>
using namespace std;

class Base {
 public:
    virtual void f( int ) {
        cout << "Base::f(int)" << endl;
    }

    virtual void f( double ) {
        cout << "Base::f(double)" << endl;
    }

   virtual void g( bool a=false, bool b=false, bool c=false, bool d=false, bool e=false, bool f=false, bool g=false, bool h=false, bool i = false ) {
        cout << i << endl;
    }
};

class Derived: public Base {
public:
    int radioParam;
    void f( complex<double> ) {
    cout << "Derived::f(complex)" << endl;
    }
    void g( bool a=false, bool b=false, bool c=false, bool d=false, bool e=false, bool f=false, bool g=false, bool h=false, bool i = false ) {
    cout << "Derived::g() " << i << endl;
    radioParam=i;
   }
};

class SecondDerived: public Derived {
public:
};


int  main() {
    Base*   ps = new SecondDerived;

    ps->g(true, true, true, true, true, true, true, true, true);

    return 0;
}