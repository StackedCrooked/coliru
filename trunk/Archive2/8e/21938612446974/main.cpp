#include <iostream>
#include <cstddef>

template<class T>
struct rank
{
    static const size_t value = 0u; 
};

// partial specialization
template<class U, int N>
struct rank<U[N]>
{
    static const size_t value = 1 + rank<U>::value; 
};

int main()
{
    rank<int, 2> r;
	return 0;
}
