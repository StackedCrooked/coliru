#include <iostream>
#include <string>

std::string x(std::string &str) {
    for (decltype(str.size()) i = 0; i < str.size(); ++i) {
		str[i] = 'x';
	}
	return str;
}

int main() {
	std::string str1 = std::string("hello world!");
	std::cout << str1;
	std::cout << " " << x(str1) << std::endl;

	std::string str2 = std::string("hello world!");
	std::cout << str2 << " " << x(str2) << std::endl;
}
