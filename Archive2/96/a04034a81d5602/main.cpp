#include <iostream>
#include <iterator>
#include <string>

int main()
{
    std::string someStrings[] = {"Hello", "World"};
	for(const auto& s : someStrings)
	{
		std::cout << s << " ";
	}

	return 0;
}