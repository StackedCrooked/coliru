#include <iostream>
using namespace std;

template <bool IsPowerOf2, int N>
struct Math
{

	static double pow(double x)
    {
#define N1 (N &(N-1))
		return Math<true, N - N1>::pow(x) *  Math<(N1&(N1 - 1))== 0, N1>::pow(x);
#undef N1
	}
};

template <int N > struct Math < true, N > { static double pow(double x){ return Math<true, N / 2>::pow(x)* Math<true, N / 2>::pow(x); } };
template < > struct Math < true, 1 > {static double pow(double x){ return x; }};

int main()
{
	cout << " Power= " << Math<false, 10>::pow(2) << endl;
	return 0;
}