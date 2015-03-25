#include <iostream>
#include <string>

template <typename T>
constexpr T add(T a, T b)
{
    return a + b;
}

int main()
{
	auto t = add(std::string("asd"), std::string("asd"));
	std::cout << t << std::endl;
	return 0;
}
