#include <iostream>
#include <string>
#include <vector>

class base {
    //dummy for now
};

class dummy: public base {
    public:
    	dummy(int a) {
    		//nothing
    	}
};

class demoA{
	public:
		demoA(std::initializer_list<base> p) {
			std::cout << "demoA(" << (void*)this << ") constructed with std::initializer_list<base>" << std::endl;
		}
		demoA(const demoA& o) {
			std::cout << "demoA(" << (void*)this << ") constructed by copy" << std::endl;
		}
		~demoA() {
			std::cout << "demoA(" << (void*)this << ") destroyed" << std::endl;
		}
};

class demoB {
	public:
		demoB(int a, std::string b) {
			std::cout << "demoB(" << (void*)this << ") constructed with std::string, int a" << std::endl;
		}
		demoB(const demoA& o) {
			std::cout << "demoB(" << (void*)this << ") constructed by copy" << std::endl;
		}
		~demoB() {
			std::cout << "demoB(" << (void*)this << ") destroyed" << std::endl;
		}
};

template<typename T>
 class proxy {
    T real;
    public:
        template<typename ... S> proxy(S ... p): real{std::move(p) ...} {}
};

using pDemoA = proxy<demoA>;
using pDemoB = proxy<demoB>;

int main() {
	std::cout << "1. Test" << std::endl;
	pDemoA{dummy{1}, dummy{1}};
	std::cout << std::endl;
	std::cout << "2. Test" << std::endl;
	pDemoB{10, "20"};
	std::cout << std::endl;
}
