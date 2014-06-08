#include <iostream>

constexpr int validate(int i)
{
    return i >= 0 ? i : throw std::exception();
}

int main()
{
	if (validate(-1))
		std::cout << "valid";
	else
		std::cout << "invalid";
}