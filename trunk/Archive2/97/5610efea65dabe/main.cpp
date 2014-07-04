#include <stdio.h>
#include <complex.h>
 
int main(void)
{
    double complex z = cexp(1.0 + 2.0*I);
    printf("%f%+fi\n", creal(z), cimag(z));
 
    return 0;
}