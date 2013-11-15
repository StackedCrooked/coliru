#include <iostream>
#include <utility>
using namespace std;

template <size_t Dim, typename N>
struct X
{
    const N n;
    
	template <typename C, 
	   class = typename std::enable_if<!std::is_same<typename std::decay<C>::type, X<Dim,N>>::value>::type>
	X(C&& n):n(std::forward<C>(n)) { std::cout << "X\n"; }
    
	X(X&& x):n(std::move(x.n)) { std::cout << "X&&\n"; }
	X(const X& x):n(x.n) { std::cout << "X&\n"; }
};

template <size_t Dim, template <size_t> class N>
X<Dim, N<Dim>> make_X(N<Dim>&& n)
{
	return X<Dim, N<Dim>>(std::forward<N<Dim>>(n));
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
	return 0;
}