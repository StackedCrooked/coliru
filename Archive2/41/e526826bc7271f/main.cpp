#include <iostream>

template <int n>
inline int factorial()
{
    return n * factorial<n - 1>();
}

template <>
inline int factorial<0>()
{
	return 1;
}

int main()
{
	std::cout << factorial<5>() << std::endl;

	return 0;
}
