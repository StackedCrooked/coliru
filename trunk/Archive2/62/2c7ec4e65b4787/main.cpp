#include <iostream>
struct A
{
    A() {std::cout << __PRETTY_FUNCTION__ << '\n';};
	~A() {std::cout << __PRETTY_FUNCTION__ << '\n';};
};

struct B
{
	A a;
	A&& f() && {return std::move(a);}
};

int main()
{
	A&& a = B().f();
	std::cout << &a;
}
