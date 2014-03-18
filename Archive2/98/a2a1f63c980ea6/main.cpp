#include <array>
#include <iostream>

using namespace std;

template<typename T, size_t N>
class counter
{
	using A = std::array<T, N>;
	A b, i, e;

public:
	counter(const A& b, const A& e) : b(b), i(b), e(e) { }

	counter& operator++()
	{
		for (size_t n = 0; n < N; ++n)
		{
			if (++i[n] == e[n])
			{
				if (n < N - 1)
					i[n] = b[n];
			}
			else
				break;
		}

		return *this;
	}

	operator bool() { return i[N - 1] != e[N - 1]; }

	T&       operator[](size_t n)       { return i[n]; }
	const T& operator[](size_t n) const { return i[n]; }
};

template<typename S, typename T, size_t N>
S& operator<<(S& s, const counter<T, N>& a)
{
	for (size_t n = 0; n < N; ++n)
		s << a[n] << " ";

	return s;
}

int main()
{
	constexpr size_t N = 3;
	using A = std::array<int, N>;

	A begin = {{0, -1,  0}};
	A end   = {{3,  1,  4}};

	for (counter<int, N> c(begin, end); c; ++c)
		cout << c << endl;
}
