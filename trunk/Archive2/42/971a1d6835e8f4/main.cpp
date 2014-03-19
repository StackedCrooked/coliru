#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


double calcPiPrecision(const int precision)
{
    const double EPS = (double) 1.0 / pow(10, precision + 1);
   double ans = 4.0;
    double ans_prev = 0.0;
	double sign = -1.0;
	double counter = 3.0;

	while ( fabs(ans - ans_prev) > EPS )
	{
		ans_prev = ans;
		ans += (4.0 / counter) * sign;
		sign = -sign;
		counter += 2.0;
	}

	return ans;
}

int main(void) 
{
	time_t start = clock();

	double fnum = calcPiPrecision(8);
	printf("%0.8lf\n", fnum);

	printf("Time taken: %0.3lf sec\n", (double) (clock() - start) / CLOCKS_PER_SEC);

	return EXIT_SUCCESS;
}