#include <iostream>

struct A
{
    A() = delete;
	A(int x)
	: x(x)
	{
	}
	virtual ~A() = 0;
	int x;
};
A::~A() = default;

struct B : virtual A
{
	B()
	{
	}
	virtual ~B() = 0;
};
B::~B() = default;

struct C : B
{
	C()
	: A(7)
	, B()
	{
	}
};

int main()
{
	C c;
	std::cout << c.x << std::endl;
}
