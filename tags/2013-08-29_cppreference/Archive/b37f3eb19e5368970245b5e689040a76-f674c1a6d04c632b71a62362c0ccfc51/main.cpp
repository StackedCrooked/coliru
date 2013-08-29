#include <iostream>
#include <string>
using namespace std;

template<class T> class C
{
public:
    volatile T x;
    static bool flag;
    static const int N=5;
protected:
    mutable T z;
public:
    C():x(static_cast<T>(NULL)),z(static_cast<T>(NULL)) {C<T>::msg("Class C default object created!");};
    explicit C(const T& x):x(x),z(x) {C<T>::msg("Class C initialized object created!");};
    explicit C(const C& c) {this->x=c.x; this->z=c.z; C<T>::msg("Class C copied object created!");};
    virtual ~C() {C<T>::msg("Class C object destroyed!");};
    C* operator&() const {return const_cast<C*>(this);};
    C& operator=(const C& c) {this->x=c.x; this->z=c.z; return *this;};
    bool operator==(const C& c) const {return (this->x==c.x && this->z==c.z);};
    void operator++() {++(this->z);};
    C& operator++(int) {(this->z)++; return *this;};
    void operator--() {--(this->z);}
    C& operator--(int) {(this->z)--; return *this;};
    static void msg(const string str) {if(C<T>::flag) {cout<<str<<endl;}};
    virtual void foo(T& x) const {x=this->z;};
}
;

template<class T> class Cx:public C<T>
{
public:
    Cx() {C<T>::msg("Class Cx object created!");};
    virtual ~Cx() {C<T>::msg("Class Cx object destroyed!");};
    virtual void foo(T& x) const {x=++(this->z);};
}
;

template<class T> class Cy:public C<T>
{
public:
    Cy() {C<T>::msg("Class Cy object created!");};
    virtual ~Cy() {C<T>::msg("Class Cy object destroyed!");};
    virtual void foo(T& x) const {x=--(this->z);};
}
;

template<class T> class Cz:public Cx<T>,public Cy<T>
{
public:
    Cz() {C<T>::msg("Class Cz object created!");};
    ~Cz() {C<T>::msg("Class Cz object destroyed!");};
}
;

template<class T> bool C<T>::flag=false;

void test_template()
{
	typedef int DATA_TYPE;
    DATA_TYPE x=7;
//    C<DATA_TYPE>::flag=true;
	C<DATA_TYPE> **p=new C<DATA_TYPE>*[C<DATA_TYPE>::N];
    C<DATA_TYPE> c;
    p[0]=new C<DATA_TYPE>(x);
    p[1]=new C<DATA_TYPE>(*p[0]);
    c=*p[1];
    p[2]=&c;
	p[3]=new Cx<DATA_TYPE>();
	p[3]->foo(x); C<DATA_TYPE>::msg(std::to_string(x));
	p[4]=new Cy<DATA_TYPE>();
	p[4]->foo(x); C<DATA_TYPE>::msg(std::to_string(x));
	p[5]=new Cz<DATA_TYPE>();
    ++*p[0];
    (*p[1])++;
	for(int i=0;i<C<DATA_TYPE>::N;i++)
	{
		if(*p[i]==c)
		{
			(*p[i])--;
			p[i]->foo(x);
			C<DATA_TYPE>::msg(std::to_string(--x));
			p[i]=NULL;
		}
		else {delete p[i];}}
    delete[] p;
}

int main()
{
	::test_template();
	cin.get();
    return static_cast<int>(NULL);
}
