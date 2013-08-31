#include <iostream>

class A {

int a;
public:
    A(int _a=0):a(_a) {
		std::cerr << "rzucam?\n";
		throw std::string("aaa");
	}
};

class B: public A {
	int b;
public:
	B(int _b=0) try
		:A(4),
		b(_b)
		{
		}
	catch(...) {
		std::cerr << "mam wyjatek\n";
	}
};
int main() {
        std::set_terminate(__gnu_cxx::__verbose_terminate_handler);

	B b; //Aborted
	return 0;
}
