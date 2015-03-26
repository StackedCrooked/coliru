#include <iostream>

struct B
{
    B() = default;
	B(int) { std::cout << "Parametrized B constructor\n"; }
};

struct D : B
{
	using B::B;
};

int main()
{
    D a;
    D b(34);
}

