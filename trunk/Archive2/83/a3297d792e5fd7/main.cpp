#include<iostream>
#include<fstream>
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
typedef unsigned u32;
int main() {
{    fstream out("sample.txt", ios::out | ios::binary);
    if (out)
    {
        for (size_t i=0; i<100; ++i)
        {
        u32 arr[10000];
        arr[0] = 54;
        out.write(reinterpret_cast<const char*>(&arr[0]), 10000*sizeof(u32));
       }
    }
}
    fstream in("sample.txt", ios::in | ios::binary);
    if (in)
    {
        u32 arr[10];
        in.read(reinterpret_cast<char*>(&arr[0]), 10*sizeof(u32));
        cout << "fread" << arr[0] << std::endl;
    }
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