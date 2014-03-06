#include <string>
#include <iostream>

class foo {
    std::string data;
public:
	explicit operator std::string(){ return data; }
	foo(std::string const &in) : data(in) {}
};

int main(){
	foo f("This is a string");

	std::cout << static_cast<std::string>(f);
}
