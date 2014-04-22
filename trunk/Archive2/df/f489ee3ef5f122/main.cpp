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
    printf("pow(2.0,2.0)      = %.1f\n", pow(2.0,2.0));
    printf("sqrt(4.0)         = %.1f\n", sqrt(4.0));        /* inverse of pow(x,2.0) */
    printf("pow(0.0,0.0)      = %.1f\n", pow(0.0,0.0));
    printf("pow(INFINITY,2.0) = %.1f\n", pow(INFINITY,2.0));
    printf("pow(NAN,2.0)      = %.1f\n", pow(NAN,2.0));
    printf("\n");
 
    /* overflow */
    errno = 0; feclearexcept(FE_ALL_EXCEPT);
    printf("pow(2.0,1024.0)   = %g\n", pow(2.0,1024.0));
    printf("%s\n",strerror(errno));
    show_fe_exceptions();
    printf("\n");
 
    /* domain error                       */
    /* "invalid" floating-point exception */
    errno = 0; feclearexcept(FE_ALL_EXCEPT);
    printf("pow(-1.0,2.1)     = %f\n", pow(-1.0,2.1));
    printf("%s\n",strerror(errno));
    show_fe_exceptions();
    printf("\n");
 
    /* pole error                                */
    /* "divide-by-zero" floating-point exception */
    errno = 0; feclearexcept(FE_ALL_EXCEPT);
    printf("pow(0.0,-1.0)     = %f\n", pow(0.0,-1.0));
    printf("%s\n",strerror(errno));
    show_fe_exceptions();
    printf("\n");
 
    errno = 0; feclearexcept(FE_ALL_EXCEPT);
    printf("pow(0.0,-2.0)     = %f\n", pow(0.0,-2.0));
    printf("%s\n",strerror(errno));
    show_fe_exceptions();
    printf("\n");
 
    errno = 0; feclearexcept(FE_ALL_EXCEPT);
    printf("pow(0.0,-INFINITY) = %f\n", pow(0.0,-INFINITY));
    printf("%s\n",strerror(errno));
    show_fe_exceptions();
 
    return 0;
}