#include <tuple>
#include <iostream>

template<typename F>
struct Not : F
{
//     using F::F;

	template<typename... A> struct ok            : std::true_type {};
	template<typename... A> struct ok<Not, A...> : std::false_type {};

	template<typename... A, typename = typename std::enable_if<
		ok<typename std::decay<A>::type...>{}
	>::type>
	Not(A&&... a) : F{std::forward<A>(a)...} {}

	template<typename... A>
	bool operator()(A&&... a) const { return !F::operator()(std::forward<A>(a)...); }
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

struct in
{
	int i, j;
	in(int i, int j) : i{i}, j{j} {}
	bool operator()(int k) const { return i <= k && k <= j; }
};

template<typename F, typename A>
void test(F f, A&& a)
{
	for (auto i : a)
		std::cout << f(i) << " ";
	std::cout << std::endl;
}

int main ()
{
	Not<eq>  f1{3}, g1{f1};
	Not<eq2> f2{}, g2{std::move(f2)};
	Not<in>  f3{2,4}, g3{f3};
	int a[] = {0,1,2,3,4,5,6};

	test(g1, a);  // 1 1 1 0 1 1 1
	test(g2, a);  // 1 1 0 1 1 1 1
	test(g3, a);  // 1 1 0 0 0 1 1
}
