#include <iostream>
#include <math.h>


int main()
{
    double width = 7.5;
	double d = .5 * width;
	double s = -9. / (2. * d * d);
	int n = int (d) + 1;
	for (int i = 1 - n; i < n; ++i) {
		std::cerr << exp (s * (i * i)) << std::endl;
	}

	return 0;
}
