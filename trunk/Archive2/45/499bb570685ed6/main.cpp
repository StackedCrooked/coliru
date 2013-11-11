#include <iostream>
#include <boost/array.hpp>

struct T
{
    T(int a, int b, int c)
		: ar({a, b}), len(c)
	{};
	
	boost::array<int, 3> ar;
	size_t len;
};

int main() {
	T x(1, 2, 3);
    std::cout << x.ar[0] << ',' << x.ar[1] << ',' << x.len << '\n';
}