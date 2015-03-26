#include <iostream>

struct B
{
    int x = 0;
	B() = default;
	B(int num) : x{num} {}
};

struct D : B
{
	using B::B;
};

int main()
{
	D a;
	D b(34);              //error is coz of this line
	std::cout << a.x << std::endl;
}