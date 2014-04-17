#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <fenv.h>
#include <string.h>
 
#pragma STDC FENV_ACCESS ON
 
void show_fe_exceptions(void)
{
    printf("current exceptions raised: ");
    if(fetestexcept(FE_DIVBYZERO))     printf(" FE_DIVBYZERO");
    if(fetestexcept(FE_INEXACT))       printf(" FE_INEXACT");
    if(fetestexcept(FE_INVALID))       printf(" FE_INVALID");
    if(fetestexcept(FE_OVERFLOW))      printf(" FE_OVERFLOW");
    if(fetestexcept(FE_UNDERFLOW))     printf(" FE_UNDERFLOW");
    if(fetestexcept(FE_ALL_EXCEPT)==0) printf(" none");
    printf("\n");
}
 
int main(void)
{
    printf("sqrt(4.0)      = %.1f\n", sqrt(4.0));
    printf("pow(2.0,2.0)   = %.1f\n", pow(2.0,2.0)); /* pow(x,2.0) is inverse of sqrt */
    printf("sqrt(INFINITY) = %.1f\n", sqrt(INFINITY));
    printf("sqrt(NAN)      = %.1f\n", sqrt(NAN));
    printf("\n");
 
    /* domain error                       */
    /* "invalid" floating-point exception */
    errno = 0; feclearexcept(FE_ALL_EXCEPT);
    printf("sqrt(-1.0)     = %f\n", sqrt(-1.0));
    printf("%s\n",strerror(errno));
    show_fe_exceptions();
 
    return 0;
}