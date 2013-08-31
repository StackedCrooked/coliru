
#include <iostream>
enum test { a, b, c };

template<test I>
struct select
{
    static void f();
};

template<>
struct select<a>
{
	static void f() { std::cout << "a"; }
};

template<>
struct select<b>
{
	static void f() { std::cout << "b"; }
};
template<>
struct select<c>
{
	static void f() { std::cout << "c"; }
};

int main()
{
	select<a>::f();
	std::cout << std::endl;
}