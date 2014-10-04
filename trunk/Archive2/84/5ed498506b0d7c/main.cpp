#include <cstdlib>
#include <cstdio>

int main()
{
    double d = 3.9e32;

	double f = abs(d);

	std::printf("%f\n", f);
}
