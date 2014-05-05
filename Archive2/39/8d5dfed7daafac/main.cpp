#include <tuple>
#include <iostream>

template<typename F>
class Not : std::tuple<F>
{
	using B = std::tuple<F>;
	F const& f() const { return std::get<0>(static_cast<B const&>(*this)); }

public:
	using B::B;

	template<typename... A>
	bool operator()(A&&... a) const { return !f()(std::forward<A>(a)...); }
};

struct eq
{
	int i;
	eq(int i) : i{i} {}
	bool operator()(int j) const { return i == j; }
};

struct eq2
{
	bool operator()(int j) const { return 2 == j; }
};

int main ()
{
	Not<eq> f{3}, g{f};
	Not<eq2> f2{}, g2{std::move(f2)};
	int a[] = {0,1,2,3,4,5,6};

	for (auto i : a)
		std::cout << g(i) << " ";  // 1 1 1 0 1 1 1
	std::cout << std::endl;

	for (auto i : a)
		std::cout << g2(i) << " ";  // 1 1 0 1 1 1 1
	std::cout << std::endl;
}
