#include <iostream>

template <typename T, size_t N>
struct A
{
	T a[N];

	template <typename... E>
 	A(E&&... e) : a{std::forward <E>(e)...} { }
};

int main ()
{
	int i = 0;
	double d{i};
	A <double, 2> x(i, 2);
	double y[2]{i, 2};
}
