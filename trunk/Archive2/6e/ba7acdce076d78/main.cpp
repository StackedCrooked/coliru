#include <array>
#include <iostream>

template <class T>
struct foo {};

struct bar
{
    template <class... Ts>
	bar(Ts&&... ts) { std::cout << "A" << std::endl; }

	template <class T, class... Ts>
	bar(const foo<T>& f, Ts&&... ts) { std::cout << "B" << std::endl; }
};

int main()
{
	auto f = foo<int>{};
	auto g = bar{f};
}