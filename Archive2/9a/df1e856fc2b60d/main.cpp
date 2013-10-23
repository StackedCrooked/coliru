#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int i, numIn, n;
    unsigned int seed;
	double x, y, pi;

	n = 1000000;
	numIn = 0;

	#pragma omp parallel private(seed, x, y) shared(n) reduction(+:numIn) 
	{
		seed = 25234 + 17 * omp_get_thread_num();
		#pragma omp for
		for (i = 0; i <= n; i++) {
			x = (double)rand_r(&seed) / RAND_MAX;
			y = (double)rand_r(&seed) / RAND_MAX;
			if (x*x + y*y <= 1) numIn++;
		}
	}
	pi = 4.*numIn / n;
	printf("asdf pi %f\n", pi);
    return 0;
}