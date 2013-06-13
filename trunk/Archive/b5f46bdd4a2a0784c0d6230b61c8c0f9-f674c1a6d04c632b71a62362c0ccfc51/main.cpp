using namespace std;
#include <iostream>
#include <string>

template<class T> class C
{
public:
    T x;
    static bool flag;
private:
    T z;
public:
    C(T x):x(x),z(x) {C<bool>::msg("Creating class C object!");};
    C():C(1) {};
    C(C& c) {this->x=c->x;this->z=c->z;};
    virtual ~C() {C<bool>::msg("Destroying class C object!");};
    C* operator&() {return this;};
    void operator++() {++(this->z);};
    C& operator++(int) {(this->z)++;return *this;};
    void operator--() {--(this->z);}
    C& operator--(int) {(this->z)--;return *this;};
    static void msg(string str) {if(C<T>::flag){cout<<str<<endl;}};
    virtual void foo(T& x) {x=this->z;};
}
;

template<class T> class Cxx:public C<T>
{
private:
    T z;
public:
    Cxx() {C<bool>::msg("Creating class Cxx object!");};
    ~Cxx() {C<bool>::msg("Destroying class Cxx object!");};
    T foo() {return this->z;};
}
;

template<class T> bool C<T>::flag=true;

int main()
{
//    int x=7;
    C<bool>::msg("START!");
    C<bool>::flag=false;
//    C<int> *p1=new C<int>(x);
//    C<int> *p2=new C<int>;
    Cxx<int> *pxx=new Cxx<int>();
//    cout<<p1->x<<endl;
//    (*p1)--;
//    p1->foo(x);
//    cout<<x<<endl;
//    delete p1;
//    delete p2;
    C<bool>::flag=true;
    delete pxx;
    return static_cast<int>(NULL);
}
