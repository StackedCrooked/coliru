#include <iostream>

class B {
public:
    virtual void f(int i = 10) { std::cout << i << '\n'; }
};

class D : public B {
public:
	void f(int i = 20) { std::cout << i << '\n'; }
};

int main()
{
	B* p = new D;
	p->f();
}