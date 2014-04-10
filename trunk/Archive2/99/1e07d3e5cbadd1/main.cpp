#include <stdio.h>
#include <complex.h>
 
int main()
{    
    double complex z = csqrt(-1.0 + 0.0*I);
    printf("%f%+fi\n", creal(z), cimag(z));
 
    z = csqrt(1.0 + 2.0*I);
    printf("%f%+fi\n", creal(z), cimag(z));
 
    return 0;
}