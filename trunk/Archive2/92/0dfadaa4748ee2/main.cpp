#include<iostream>
#include<complex>
using namespace std;

class base {
public:
    virtual void f( int );
    virtual void f( double );
    virtual void g( int i = 10 );
    virtual ~base() {}
};

void base::f( int ) {
    cout << "base::f(int)" << endl;
}

void base::f( double ) {
    cout << "base::f(double)" << endl;
}

void base::g( int i ) {
    cout << i << endl;
}

class derived: public base {
public:
    void f( complex<double> );
    void g( int i = 20 );
};

void derived::f( complex<double> ) {
    cout << "derived::f(complex)" << endl;
}

void derived::g( int i ) {
    cout << "derived::g() " << i << endl;
}

int main() {
    base    b;
    derived d;
    base*   pb = new derived;

    b.f(1.0);
    d.f(1.0);
    pb->f(1.0);

    b.g();
    d.g();
    pb->g();

    delete pb;
}