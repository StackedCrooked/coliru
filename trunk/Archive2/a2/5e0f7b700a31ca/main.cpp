#include <iostream>

class A{};

class C : /*A*/ {
public:
	short a;
//private:
	char b;
//virtual void meh(){};
//    C(){};
public:
	void foo(){ std::cout << " a:"<< (long) &a <<" b:" << (long) &b << std::endl;}

};

class EC : public C {
	char c;
public:
	void foo(){ C::foo(); std::cout << " &c" << (long) &c << std::endl;}
};



int main() {
static_assert(sizeof(short) == 2,"");
std::cout << sizeof(C);

std::cout << sizeof(EC);

EC ec;
ec.foo();

}
