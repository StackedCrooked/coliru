#include <stdio.h>
#include <math.h>
#include <complex.h>
 
int main(void)
{
    double complex z = cexp(-I * 2 * PI * 1 * 0 / 10601);
    printf("%f%+fi\n", creal(z), cimag(z));
 
    return 0;
}