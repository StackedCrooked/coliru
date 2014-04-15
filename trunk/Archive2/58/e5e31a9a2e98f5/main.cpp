#include <stdio.h>
#include <math.h>
 
int main()
{
    printf ("fmax(2.0,1.0)        = %.1f\n", fmax(2.0,1.0));
    printf ("fmax(-0.0,+0.0)      = %.1f\n", fmax(-0.0,+0.0));
    printf ("fmax(-INFINITY,+0.0) = %.1f\n", fmax(-INFINITY,+0.0));
    printf ("fmax(NAN,1.0)        = %.1f\n", fmax(NAN,1.0));
    printf ("fmax(NAN,NAN)        = %.1f\n", fmax(NAN,NAN));
 
    return 0;
}