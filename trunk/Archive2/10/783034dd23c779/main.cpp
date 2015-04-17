#include <boost/shared_ptr.hpp>
#include <iostream>

struct A {
    virtual int foo() {return 0;}
};

struct B : public A {
	int foo() {return 1;}
};

int main() {
	boost::shared_ptr<A> a;
	{
		boost::shared_ptr<B> b(new B());
		a = b;
	}
	
	std::cout << a->foo() << std::endl;
}
