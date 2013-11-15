#include <iostream>
#include <utility>
using namespace std;

template <size_t Dim, template <size_t, typename...> class N, typename... Rest>
struct X
{
    const N<Dim, Rest...> n;
	template <typename C, 
	class = typename std::enable_if<!std::is_same<typename std::decay<C>::type, X>::value>::type>
	X(C&& n):n(std::forward<C>(n)) { std::cout << "X\n"; }
	X(X&& x):n(std::move(x.n)) { std::cout << "X&&\n"; }
	X(const X& x):n(x.n) { std::cout << "X&\n"; }
};

template <size_t Dim, template <size_t, typename...> class N, typename... Rest>
X<Dim, N> make_X(N<Dim, Rest...>&& n)
{
	return {std::forward<N<Dim, Rest...>>(n)};
}
template <size_t Dim, template <size_t, typename...> class N, typename... Rest>
X<Dim, N> make_X(const N<Dim, Rest...>& n)
{
    return {n};
}


template <size_t Dim>
struct Y
{
	Y() { std::cout << "Y\n"; }
	Y(Y&&) { std::cout << "Y&&\n"; }
	Y(const Y&) { std::cout << "Y&\n"; }
};

int main() {
	// your code goes here
	auto someX = make_X(Y<2>());
    auto someY = Y<2>();
    auto someX2 = make_X(someY);
    auto someX3 = make_X(someX2);
	return 0;
}