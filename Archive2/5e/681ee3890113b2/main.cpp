#include <stdio.h>
#include <math.h>
 
int main(void)
{
    printf ("fmin(2.0,1.0)        = %.1f\n", fmin(2.0,1.0));
    printf ("fmin(-0.0,+0.0)      = %.1f\n", fmin(-0.0,+0.0));
    printf ("fmin(-INFINITY,+0.0) = %.1f\n", fmin(-INFINITY,+0.0));
    printf ("fmin(NAN,1.0)        = %.1f\n", fmin(NAN,1.0));
    printf ("fmin(NAN,NAN)        = %.1f\n", fmin(NAN,NAN));
 
    return 0;
}