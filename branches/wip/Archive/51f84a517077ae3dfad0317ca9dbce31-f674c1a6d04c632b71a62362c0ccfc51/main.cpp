#include <iostream>
using namespace std;

template<class T> class C
{
public:
    T x;
private:
    T z;
public:
    C(T x):x(x),z(x) {};
    C():C(1) {};
    C(C& c) {this->x=c->x;this->z=c->z;};
    virtual ~C() {};
    C* operator&() {return this;};
    void operator++() {++(this->z);};
    C& operator++(int) {(this->z)++;return *this;};
    void operator--() {--(this->z);}
    C& operator--(int) {(this->z)--;return *this;};
    virtual T foo() {return this->z;};
}
;

template<class T> class Cxx:public C<T>
{
public:
    T foo() {return this->z;};
//private:
//    T z;
}
;

int main()
{
    int x=7;
    C<int> *p1=new C<int>(x);
    C<int> *p2=new C<int>;
    Cxx<int> *pxx=new Cxx<int>();
    cout<<p1->x<<endl;
    (*p1)++;
    cout<<p1->foo()<<endl;
    delete p1;
    delete p2;
    delete pxx;
    return static_cast<int>(NULL);
}
