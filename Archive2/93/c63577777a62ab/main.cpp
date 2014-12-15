#include <iostream>

constexpr bool equal( char const* lhs, char const* rhs )
{
    while (*lhs || *rhs)
		if (*lhs++ != *rhs++)
			return false;
	return true;
}

int main()
{
	constexpr bool a = equal("A", "B");
	constexpr bool b = equal("A", "A");
	constexpr bool c = equal("A", "AB");
	std::cout << a << b << c;
}
