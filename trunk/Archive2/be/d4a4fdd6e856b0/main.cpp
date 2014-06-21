#include <iostream>
#include <utility>

// Partial application library code

template <typename T, typename F>
struct partial_functor_t
{
    F f;
	T && t;

	template<typename ... Args>
	decltype(auto) operator ()(Args && ... args)
	{
		return f(std::forward<T>(t), std::forward<Args>(args) ...);
	}
};

template<typename F, typename T, typename ... Args>
decltype(auto) partial(F f, T && t, Args && ... args)
{
	return partial(
		partial_functor_t<T, F>{std::move(f), std::forward<T>(t)},
		std::forward<Args>(args) ...);
}

template<typename F>
decltype(auto) partial(F f)
{
	return f;
}

// Example use

int sum(bool a, char b, short c, int d, long e)
{
    return a + b + c + d + e;
}

int main()
{
    auto f = partial(sum, 1, 2, 3);
	std::cout << f(4, 5) << "\n";
	std::cout << f(6, 7) << "\n";
}