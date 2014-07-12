#include <iostream>
#include <sstream>
#include <string>
#include <cstdio>
#include <cstdlib>

int main()
{
    double d{0}; std::string s;

	std::istringstream iss("0xABp-4");
	iss >> d;
	iss.clear();
	iss >> s;
	std::cout << d << ", '" << s << "'\n";
}
