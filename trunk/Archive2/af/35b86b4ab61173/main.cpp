#include <iostream>

struct A {
    A() { std::cout << "A" << std::endl; }
	~A() { std::cout << "~A" << std::endl; }
};

struct B {
	B() { throw 1; }
};
struct C {
	A a_;
	B b_;
};

int main() {
	try {
		C c;
	}
	catch (...){
	}
}