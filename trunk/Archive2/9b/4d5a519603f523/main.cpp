#include <iostream>
#include <math.h>
#include <vector>

int main()
{
    double width = 8.75;
	double d = .5 * width;
	double s = -9. / (2. * d * d);
	int n = int (d) + 1;
    std::vector< double > kernel (n);
	for (int i = 0; i < n; ++i) {
        kernel[i] = exp (s * (i * i));
		std::cerr << kernel[i] << std::endl;
	}
    
	return 0;
}
