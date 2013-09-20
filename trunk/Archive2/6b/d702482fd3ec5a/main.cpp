#include <iostream>


using namespace std;

class A
{
public:
    void f() const { cout << this << " -> A::f()" << endl; }
};

class B : public A
{
public:
	void f() const { cout << this << " -> B::f()" << endl; }
	
	void callB() const { this->f(); }
	
	void callA() const { this->A::f(); }
};

int main()
{
	B b;
	
	b.callA();
	b.callB();
}
