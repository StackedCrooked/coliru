#include <array>
#include <iostream>

using namespace std;

template<size_t N>
using size = std::integral_constant<size_t, N>;

template<typename T, size_t N>
class counter : std::array<T, N>
{
    using A = std::array<T, N>;
	A b, e;

	template<size_t I = 0>
	void inc(size<I> = size<I>())
	{
		if (++_<I>() != std::get<I>(e))
			return;

		_<I>() = std::get<I>(b);
		inc(size<I+1>());
	}

	void inc(size<N-1>) { ++_<N-1>(); }

public:
	counter(const A& b, const A& e) : A(b), b(b), e(e) { }

	counter& operator++() { return inc(), *this; }

	operator bool() { return (*this)[N - 1] != e[N - 1]; }

	template<size_t I>
	T& _() { return std::get <I>(*this); }

	template<size_t I>
	constexpr const T& _() const { return std::get <I>(*this); }
};

int main()
{
	constexpr size_t N = 3;
	using A = std::array<int, N>;

	A begin = {{0, -1,  0}};
	A end   = {{3,  1,  4}};

	for (counter<int, N> c(begin, end); c; ++c)
		cout << c._<0>() << " " << c._<1>() << " " << c._<2>() << endl;
}
