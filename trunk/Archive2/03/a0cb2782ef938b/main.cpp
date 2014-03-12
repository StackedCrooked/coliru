#include <iostream>
#include <string>

void copy()
{
    std::string str;
	if (!(std::cin >> str))
		return;
	std::cout << str << '\n';
	copy();
}

int main()
{
	copy();
}
