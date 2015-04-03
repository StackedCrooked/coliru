#include <string>
#include <iostream>

int main() { 
    std::string input {"1234"};
	std::string::size_type pos = input.find("");
	if (pos != std::string::npos)
		std::cout << pos;
}
