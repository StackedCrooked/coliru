#include <cstdio>

template<typename T>
auto f = [] { puts("f"); };


int main()
{
    f<int>;
	return 0;
}