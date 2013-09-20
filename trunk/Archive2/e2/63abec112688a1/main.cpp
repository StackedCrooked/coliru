#include <iostream> 

template <class T>
struct Base {
    void foo() {
		T *concrete = static_cast<T*>(this);
		concrete->foo();
	};
	void bar() {std::cout << "Base" << std::endl; }
};

struct Derived : public Base<Derived> {
	void foo() {std::cout << "Derived" << std::endl;}
};

int main() {
	Base<Derived> *b = new Derived;
	b->foo();
	b->bar();
}