using namespace std;
#include <iostream>
#include <string>

template<class T> class C
{
public:
    T x;
private:
    T z;
public:
    C(T x):x(x),z(x) {this->msg("Creating class C object!");};
    C():C(1) {};
    C(C& c) {this->x=c->x;this->z=c->z;};
    ~C() {this->msg("Destroying class C object!");};
    C* operator&() {return this;};
    void operator++() {++(this->z);};
    C& operator++(int) {(this->z)++;return *this;};
    void operator--() {--(this->z);}
    C& operator--(int) {(this->z)--;return *this;};
    static void msg(string str) {cout<<str<<endl;};
    virtual void foo(T& x) {x=this->z;};
}
;

template<class T> class Cxx:public C<T>
{
private:
    T z;
public:
    Cxx() {this->msg("Creating class Cxx object!");};
    ~Cxx() {this->msg("Destroying class Cxx object!");};
    T foo() {return this->z;};
}
;

int main()
{
//    int x=7;
    C<bool>::msg("START!");
//    C<int> *p1=new C<int>(x);
//    C<int> *p2=new C<int>;
    Cxx<int> *pxx=new Cxx<int>();
//    cout<<p1->x<<endl;
//    (*p1)--;
//    p1->foo(x);
//    cout<<x<<endl;
//    delete p1;
//    delete p2;
    delete pxx;
    return static_cast<int>(NULL);
}
