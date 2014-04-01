#include <iostream>

using namespace std;

template<size_t I>
using size = std::integral_constant <size_t, I>;

template<size_t N, typename S, typename... U>
struct overload_base;

template<size_t N, typename R, typename... A, class... U>
struct overload_base <N, R(A...), U...> : overload_base<N + 1, U...>
{
protected:
    using overload_base<N + 1, U...>::_call;
	virtual R _call(size<N>, A...) = 0;
};

template<int N, typename R, typename... A>
struct overload_base<N, R(A...)>
{
protected:
	virtual R _call(size<N>, A...) = 0;
};

template<class... S>
struct overload : overload_base<0, S...>
{
	template<int N, typename... A>
	auto call(A&&... a)
	-> decltype(this->_call(size<N>(), std::forward<A>(a)...))
		{ return this->_call(size<N>(), std::forward<A>(a)...); }
};


struct test : overload<void(int const&), void(bool const&)>
{
protected:
	virtual void _call(size<0>, int  const& a) { cout << a << endl; }
	virtual void _call(size<1>, bool const& a) { cout << a << endl; }
};

int main()
{
	test t;
	t.call<0>(100500);
	t.call<1>(true);
}
