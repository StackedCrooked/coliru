#include <cmath>
#include <limits>
#include <iostream>

template<typename T>
struct foo
{
    T val;

	foo(T v = T()) : val(v) { sync(v); }
	foo& operator=(T v) { val = v; sync(v); return *this; }

	template<typename U> foo(U v) : foo(T(v)) {}
	template<typename U> foo& operator=(U v) { return *this = T(v); }

	operator T&() { return val; }
	operator const T&() const { return val; }

	using lim = std::numeric_limits<int>;

	static int& min() { static int e = lim::max(); return e; }
	static int& max() { static int e = lim::min(); return e; }

	static void sync_min(T e) { if (e < min()) min() = int(e); }
	static void sync_max(T e) { if (e > max()) max() = int(e); }

	static void sync(T v)
	{
		v = std::abs(v);
		T e = v == 0 ? T(1) : std::log10(v);
		sync_min(std::floor(e)); sync_max(std::ceil(e));
	}
};

int main ()
{
	using T = foo<float>;
	T x;

	for (T e = -10.6; e <= 30.4; e += .2)
		x = std::pow(10, e);

	std::cout << T::min() << " " << T::max() << std::endl;
}
