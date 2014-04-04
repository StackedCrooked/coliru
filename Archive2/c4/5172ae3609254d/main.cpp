#include <stdio.h>
#include <math.h>
#include <fenv.h>
#include <errno.h>
#include <float.h>
 
int main()
{
    printf("FLT_RADIX = %d\n", FLT_RADIX);
    printf("\n");
 
    printf("scalbn(1.0,+1023)   = %g\n",    scalbn(1.0,+1023));     /* 1 * 2^(+1023)  */
    printf("scalbn(1.0,-1074)   = %g\n",    scalbn(1.0,-1074));     /* 1 * 2^(-1074)  */
    printf("scalbn(5.0,0)       = %+.1f\n", scalbn(5.0,0));         /* 5 * 2^0        */
    printf("scalbn(+0.0,1)      = %+.1f\n", scalbn(+0.0,1));        /* 0 * 2^1        */
    printf("scalbn(-0.0,1)      = %+.1f\n", scalbn(-0.0,1));
    printf("scalbn(+INFINITY,1) = %+f\n",   scalbn(+INFINITY,1));   /* INFINITY * 2^1 */
    printf("scalbn(-INFINITY,1) = %+f\n",   scalbn(-INFINITY,1));
    printf("\n");
 
    {
        #pragma STDC FENV_ACCESS ON
 
        /* "inexact" and "overflow" floating-point exceptions */
        /* Overflow does not set errno.                       */
        /* 1 * 2^(+1024)                                      */
        errno = 0; feclearexcept(FE_ALL_EXCEPT);
        printf("scalbn(1.0,1024)       = %f\n",   scalbn(1.0,1024));
        printf("errno                  = %d\n",   errno);
        printf("FE_INEXACT,FE_OVERFLOW = 0x%x\n", fetestexcept(FE_ALL_EXCEPT));
        printf("\n");
 
        /* "inexact" and "underflow" floating-point exceptions */
        /* Underflow does not set errno.                       */
        /* 1 * 2^(-1075)                                       */
        errno = 0; feclearexcept(FE_ALL_EXCEPT);
        printf("scalbn(1.0,-1075)       = %g\n",   scalbn(1.0,-1075));
        printf("errno                   = %d\n",   errno);
        printf("FE_INEXACT,FE_UNDERFLOW = 0x%x\n", fetestexcept(FE_ALL_EXCEPT));
 
    } // end FENV_ACCESS block
 
    return 0;
}