#include <iostream>

class A{};
struct B{ /*~B(){};*/};

class C /*: A */{
public:
    B bar;
	short a;
//private:
	char b;
 
public:
//    virtual void meh(){};

//    C(){};
//    ~C(){};
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
