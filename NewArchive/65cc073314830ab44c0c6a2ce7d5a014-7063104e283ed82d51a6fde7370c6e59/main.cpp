#include <iostream>
#include <iomanip>
#include <regex>

int main()
{
    std::regex r("http://");

	std::cout << std::boolalpha;
	std::cout << std::regex_match("http://", r);

	std::cin.get();
	return 0;
}