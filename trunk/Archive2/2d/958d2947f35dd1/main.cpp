#include <float.h>
#include <stdio.h>


int main()
{
    double pi = -DBL_MAX;
	double pi_plus = -DBL_MAX + 1e+292;

	printf("%g\n", pi);
	printf("%g\n", pi_plus);
    printf("%i\n", pi == pi_plus);
  
  return 0;
}

