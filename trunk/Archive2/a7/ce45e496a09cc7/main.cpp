#include <cmath>
#include <limits>
#include <iostream>

template<typename T>
class foo
{
    T val;

	using lim = std::numeric_limits<int>;

	static int& min_val() { static int e = lim::max(); return e; }
	static int& max_val() { static int e = lim::min(); return e; }

	static void sync_min(T e) { if (e < min_val()) min_val() = int(e); }
	static void sync_max(T e) { if (e > max_val()) max_val() = int(e); }

	static void sync(T v)
	{
		v = std::abs(v);
		T e = v == 0 ? T(1) : std::log10(v);
		sync_min(std::floor(e)); sync_max(std::ceil(e));
	}

public:
	foo(T v = T()) : val(v) { sync(v); }
	foo& operator=(T v) { val = v; sync(v); return *this; }

	template<typename U> foo(U v) : foo(T(v)) {}
	template<typename U> foo& operator=(U v) { return *this = T(v); }

	operator T&() { return val; }
	operator const T&() const { return val; }

	static int min() { return min_val(); }
	static int max() { return max_val(); }
};

int main ()
{
    using F = foo<float>;
	F x;

	for (F e = -10.2; e <= 30.4; e += .2)
		x = std::pow(10, e);

	std::cout << F::min() << " " << F::max() << std::endl;  // -11 31
}
