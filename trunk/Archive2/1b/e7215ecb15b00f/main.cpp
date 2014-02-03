#include <iostream> 

typedef char Pc;

void foo(unsigned Pc) {
    std::cout << "foo(unsigned Pc)\n";
}

void foo(unsigned char) {
	std::cout << "foo(unsigned char)\n";
}

int main() {
	unsigned char c{};
	unsigned int i{};
	foo(c);
	foo(i);
}