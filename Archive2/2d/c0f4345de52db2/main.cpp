#include <iostream> 

template <class T>
struct Base {
    void foo() {};
	void bar() {std::cout << "Base" << std::endl; }
};

struct Derived : public Base<Derived> {
	void foo() {std::cout << "Derived" << std::endl;}
};

int main() {
	Derived d;
	d.foo();
	d.bar();
}