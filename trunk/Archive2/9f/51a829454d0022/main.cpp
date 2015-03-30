#include <array>
#include <iostream>

template <class T>
struct foo {};

template <class T>
struct is_foo { static constexpr auto value = false; };

template <class T>
struct is_foo<foo<T>> { static constexpr auto value = true; };

struct bar
{
    template <class T, class... Ts, typename std::enable_if_t<!is_foo<std::decay_t<T>>::value, int> = 0>
	bar(T&& t, Ts&&... ts) { std::cout << "A" << std::endl; }

	template <class T, class... Ts>
	bar(const foo<T>& f, Ts&&... ts) { std::cout << "B" << std::endl; }
};

int main()
{
	auto f = foo<int>{};
	auto g = bar{f};
}