#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <fenv.h>
#define PI acos(-1)
 
int main()
{
    printf("sin(PI/2.0)   = %.1f\n", sin(PI/2.0));
    printf("sin(+0.0)     = %.1f\n", sin(+0.0));
    printf("sin(-0.0)     = %.1f\n", sin(-0.0));
    printf("sin(NAN)      = %.1f\n", sin(NAN));
    printf("\n");
 
    /* domain error                       */
    /* "invalid" floating-point exception */
    /* same with sin(-INFINITY)           */
    errno = 0; feclearexcept(FE_ALL_EXCEPT);
    printf("sin(INFINITY) = %f\n", sin(INFINITY));
    printf("errno         = %d\n", errno);
    printf("FE_INVALID    = %d\n", fetestexcept(FE_ALL_EXCEPT));
 
    return 0;
}