#include <iostream>

template <typename A, typename B>
using ternary = decltype(true ? std::declval <A>() : std::declval <B>());

template <template <typename...> class F>
struct test
{
    template <typename... A, typename T = F <A...> >
	static std::true_type call(int);

	template <typename... A>
	static std::false_type call(...);
};

template <template <typename...> class F, typename... A>
using sfinae = decltype(test <F>::template call <A...>(0));

template <typename T> struct X { };

template <typename T> struct Y
{
	template <typename A>
	Y(A&& a) { }
};

int main ()
{
	using A = X <int>;
	using B = X <double>;
	using C = Y <int>;
	using D = Y <double>;
	sfinae <ternary, A, B>{};
	sfinae <ternary, C, D>{};
}
