#include <tuple>
#include <utility>
#include <iostream>

template<size_t... I> struct sizes { using type = sizes<I...>; };

template<size_t N, size_t K = 0, size_t... I>
struct idx_t : idx_t<N, K+1, I..., K> {};

template<size_t N, size_t... I>
struct idx_t<N, N, I...> : sizes<I...> {};

template<size_t N>
using idx = typename idx_t<N>::type;

struct A {
    A(int) { std::cout << "This is int\n"; }
	A(unsigned, double) { std::cout << "This is unsigned, double\n"; }
};

struct B {
	B(char, int) { std::cout << "This is char, int\n"; }
};

template <typename T>
struct C : public T
{
    template<typename... A>
    C(std::tuple<A...>&& a, double x) :
		C(std::move(a), x, idx<sizeof...(A)>{}) { }

    template<typename... A, size_t... I>
    C(std::tuple<A...>&& a, double x, sizes<I...>) :
		T(std::get<I>(std::move(a))...) { std::cout << "This is double\n"; }
};

int main() {
	C<A> p(std::forward_as_tuple(1),      1.0);
	C<A> r(std::forward_as_tuple(1u, 2.), 1.0);
	C<B> q(std::forward_as_tuple('c', 0), 1.0);
}
