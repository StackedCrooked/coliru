#include <iostream>

template <typename F, typename T>
struct partial_functor_t
{
    F f;
	T && t;

	template<typename ... Args>
	auto operator ()(Args && ... args)
	{
		return f(std::forward<T>(t), std::forward<Args>(args) ...);
	}
};

template<typename F>
auto partial(F f)
{
	return f;
}

template<typename F, typename T, typename ... Args>
auto partial(F f, T && t, Args && ... args)
{
	return partial(partial_functor_t<F, T>{f, std::forward<T>(t)}, std::forward<Args>(args) ...);
}

int sum(int a, int b, int c, int d, int e)
{
	return a + b + c + d + e;
}

int main()
{
	auto f1 = partial(sum, 1, 2);
	auto f2 = partial(f1, 3);
	std::cout << f2(4, 5) << "\n";
}