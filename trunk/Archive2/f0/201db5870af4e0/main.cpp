#include <iostream>

class Base {
public:
    virtual void f(int i = 10) { std::cout << i << '\n'; }
};

class Derived : public Base {
public:
	void f(int i = 20) { std::cout << i << '\n'; }
};

int main()
{
	Base* p = new Derived;
	p->f();
}