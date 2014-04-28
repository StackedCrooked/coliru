#include <iostream>
struct S  {
    short a;
	char b;
public:
        void foo(){ std::cout << " a:"<< (long) &a <<" b:" << (long) &b << std::endl;}

};


class C {
public:
	short a;
	char b;
public:
	void foo(){ std::cout << " a:"<< (long) &a <<" b:" << (long) &b << std::endl;}

};

class EC : public C {
private:
   char c;
public:
	void foo(){ C::foo(); std::cout << " &c" << (long) &c << std::endl;}
};


struct ES : private S {
	char c;
	void foo(){ S::foo();std::cout << " c:" <<(long) &c << std::endl;}

};

int main() {
static_assert(sizeof(short) == 2,"");
static_assert(sizeof(S) == 4,"");
std::cout << sizeof(C);

std::cout << sizeof(EC);
std::cout << sizeof(ES);

EC ec;
ES es;
ec.foo();
es.foo();

}
