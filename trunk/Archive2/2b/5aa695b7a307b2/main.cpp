#include <type_traits>
#include <iostream>

using namespace std;

template <typename F>
struct fold
{
	template <typename A>
	constexpr typename std::decay <A>::type
	operator()(A&& a) const { return std::forward <A>(a); }

	template <typename A, typename... An>
	constexpr typename std::common_type <A, An...>::type
	operator()(A&& a, An&&... an) const
		{ return F()(std::forward <A>(a), operator()(std::forward <An>(an)...)); }
};

struct max_fun
{
	template <typename A, typename B>
	constexpr typename std::common_type <A, B>::type
	operator()(A&& a, B&& b) const
		{ return a > b ? std::forward <A>(a) : std::forward <B>(b); }
};

using max = fold <max_fun>;

int main ()
{
	cout << ::max()(5, 9, -2, 0.1) << endl;
}

