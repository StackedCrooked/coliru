#include <iostream>

#define USE_CPP_INT

#ifdef USE_CPP_INT
#include <boost/multiprecision/cpp_int.hpp>
typedef boost::multiprecision::cpp_int ull;
#else
typedef unsigned long long ull;
#endif

ull gcd(ull q, ull r)
{
    return r ? gcd(r, q%r) : q;
}

ull f(int x, int y, ull a, ull b, ull B)
{
	int max_xy = x > y ? x : y;
	// fib[max_xy]
	ull* fib = new ull[max_xy];
	// find all fib[i]
	fib[0] = fib[1] = 1;
	for (int i = 2; i < max_xy; ++i)
		fib[i] = fib[i-1] + fib[i-2];
	
	// F[x+1][y+1]
	ull** F = new ull*[x+1];
	for (int i = 0; i <= x; ++i) F[i] = new ull[y+1];
	// fill top horizontal line
	for (int i = 0; i <= x; ++i) F[i][0] = i;
	// fill left vertical line
	for (int j = 0; j <= y; ++j) F[0][j] = j;
	// init the rest with gcd(fib[i-1], fib[j-1])
	int min_xy = x > y ? y : x;
	for (int i = 1; i <= min_xy; ++i)
		for (int j = i; j <= min_xy; ++j)
			F[i][j] = F[j][i] = gcd(fib[i-1], fib[j-1]);
	if (x < y)
		for (int i = 1; i <= x; ++i)
			for (int j = min_xy+1; j <= y; ++j)
				F[i][j] = gcd(fib[i-1], fib[j-1]);
	else if (y < x)
		for (int i = min_xy+1; i <= x; ++i)
			for (int j = 1; j <= y; ++j)
				F[i][j] = gcd(fib[i-1], fib[j-1]);
		
	delete [] fib; // free fib[]
	
	// fill the rest of F[][]
	for (int i = 1; i <= x; ++i)
		for (int j = 1; j <= y; ++j)
			F[i][j] = (F[i-1][j]*a + F[i][j-1]*b + F[i][j])%B;
	// get result		
	ull res = F[x][y];
	// free F[][]
	for (int i = 0; i <= x; ++i) delete [] F[i];
	delete [] F;
			
	return res;
}

int main()
{
	int x, y;
	unsigned long long a, b, B;
	int n;
	std::cin >> n;
	for (int i = 0; i < n; ++i)
	{
		std::cin >> x >> y >> a >> b >> B;
		std::cout << f(x,y,a,b,B)  << "\n";
	}
}