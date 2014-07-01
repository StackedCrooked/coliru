#include <iostream>
#include <type_traits>

int main()
{
    std::cout << "char == signed char? " << std::is_same<char, signed char>::value << std::endl;
	std::cout << "int == signed int? " << std::is_same<int, signed int>::value << std::endl;

	return 0;
}
