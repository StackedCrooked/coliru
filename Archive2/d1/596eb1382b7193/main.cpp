#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <fenv.h>
 
#pragma STDC FENV_ACCESS ON
int main(void)
{
    double pi = acos(-1);
    // typical usage
    printf("sin(pi/6) = %f\n", sin(pi/6));
    printf("sin(pi/2) = %f\n", sin(pi/2));
    printf("sin(-3*pi/4) = %f\n", sin(-3*pi/4));
    // special values
    printf("sin(+0) = %f\n", sin(0.0));
    printf("sin(-0) = %f\n", sin(-0.0));
    // error handling 
    feclearexcept(FE_ALL_EXCEPT);
    printf("sin(INFINITY) = %f\n", sin(INFINITY));
    if(fetestexcept(FE_INVALID)) puts("    FE_INVALID raised");
}