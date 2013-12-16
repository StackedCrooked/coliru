#include <stdio.h>
#include <string.h>
#include <math.h>

int main()
{
    double  f, m;
    int e;
    
    f = 6.0;
    
    // Extract matissa and exponent
    m = frexp(f,&e);
    printf("Test= %f %f %d\n", f, m, e);
    
    // Reverse
    int m1=75, e1 =3;
    double f1;
    
    f1 = ldexp(((double)m1)/100,e1);
    printf("f1= %f\n", f1);
}
