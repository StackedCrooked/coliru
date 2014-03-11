#include <iostream>

using namespace std;

template <size_t N>
using size = std::integral_constant <size_t, N>;

template <typename F, size_t L, size_t N = 0, bool = (N < L)>
struct idx
{
    template <size_t R = 1>
    inline constexpr decltype(F()(size <0>()))
	operator()(size_t I, size <R> = size <R>()) const
	{
		return I%2 ? idx <F, L, N+R>()(--I/2, size <2*R>()) :
		       I   ? idx <F, L, N  >()(  I/2, size <2*R>()) :
		       F()(size <N>());
	}
};

template <typename F, size_t L, size_t N>
struct idx <F, L, N, false>
{
	template <size_t R>
	inline constexpr decltype(F()(size <0>()))
	operator()(size_t I, size <R>) const { return F()(size <4>()); }
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
