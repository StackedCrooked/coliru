#include <iostream>

using namespace std;

template <size_t N>
using size = std::integral_constant <size_t, N>;

template <
    typename F, size_t L,
    size_t R = 1, size_t N = 0, bool = (R < 2 * L && N < L)
>
struct idx
{
    inline constexpr decltype(F()(size <0>()))
	operator()(size_t i) const
	{
		return i%2 ? idx <F, L, 2*R, N+R>()(--i/2) :
		       i   ? idx <F, L, 2*R, N  >()(  i/2) :
		       F()(size <N>());
	}
};

template <typename F, size_t L, size_t R, size_t N>
struct idx <F, L, R, N, false>
{
	inline constexpr decltype(F()(size <0>()))
	operator()(size_t I) const { return F()(size <0>()); }
};

struct F
{
	template <size_t I>
	constexpr size_t operator()(size <I>) const { return I; }
};

int main ()
{
	constexpr size_t L = 10;
	idx <F, L> f;
	for (size_t i = 0; i < L; ++i)
		cout << f(i) << " ";

	cout << endl;
}
