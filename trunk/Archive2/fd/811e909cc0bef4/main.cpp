#include <stdio.h>        /* printf                         */
#include <complex.h>      /* complex, float complex, I, ... */
 
int main () {
 
    #ifdef __STDC_IEC_559_COMPLEX__
           printf("_STDC_IEC_559_COMPLEX__ defined\n");
    #else
           printf("_STDC_IEC_559_COMPLEX__ not defined\n");
    #endif
    #ifdef __STDC_NO_COMPLEX__
           printf("__STDC_NO_COMPLEX__ defined\n");
    #else
           printf("__STDC_NO_COMPLEX__ not defined\n");
    #endif
    printf("\n");
 
    printf("%2zu\n", sizeof(float complex));           /*  8 */
    printf("%2zu\n", sizeof(double complex));          /* 16 */
    printf("%2zu\n", sizeof(long double complex));     /* implementation-defined */
 
    /* Two macros represent the imaginary unit “i”: */
    /*      _Complex_I                              */
    /*      I                                       */
    printf("%.1f%+.1fi\n", creal(_Complex_I),cimag(_Complex_I));
    printf("%.1f%+.1fi\n", creal(I),cimag(I));
 
    /* The central property of the imaginary unit:  i*i is -1. */
    printf("%.1f%+.1fi\n", creal(1.0*_Complex_I*1.0*_Complex_I),
                           cimag(1.0*_Complex_I*1.0*_Complex_I));
    printf("%.1f%+.1fi\n", creal(1.0*I*1.0*I),cimag(1.0*I*1.0*I));
 
    /* Use the macros to define complex constants. */
    double complex z1 = 1.0 + 2.0*I;
    double complex z2 = 2.0 + 4.0*_Complex_I;
 
    /* Sum and print. */
    double complex z3 = z1+z2;
    printf("%.1f%+.1fi\n", creal(z3),cimag(z3));
 
    /* When the macro named "I" conflicts in an application, */
    /* define a new macro named "J" or "j".                  */
    #undef I
    #define J _Complex_I
    z1 = 1.5 + 2.5*J;
 
    return 0;
}