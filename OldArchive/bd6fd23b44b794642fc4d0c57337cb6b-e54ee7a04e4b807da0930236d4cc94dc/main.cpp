#include <iostream>
#include <string>

std::string x(std::string &str) {
    for(auto &s : str) {
		s = 'x';
	}
	return str;
}

int main() {
	std::string str1("hello world!");
	std::cout << str1;
	std::cout << " " << x(str1) << std::endl;

	std::string str2("hello world!");
	std::cout << str2 << " " << x(str2) << std::endl;
}