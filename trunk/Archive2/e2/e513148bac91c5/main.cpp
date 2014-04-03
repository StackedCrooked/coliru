#include <math.h>
#include <stdio.h>
#include <float.h>
#include <fenv.h>
 
int main()
{
    float from1 = 0, to1 = nextafterf(0, 1);
    printf("The next representable float after %.2f (%a) is %.20g (%a)\n",
           from1, from1, to1, to1);
 
    float from2 = 1, to2 = nextafterf(1, 2);
    printf("The next representable float after %.2f (%a) is %.23f (%a)\n",
           from2, from2, to2, to2);
 
    double from3 = nextafter(0.1, 0), to3 = 0.1;
    printf("The number 0.1 lies between two valid doubles:\n    %.56f (%a)\nand %.55f  (%a)\n",
           from3, from3, to3, to3);
 
    {
        #pragma STDC FENV_ACCESS ON
        feclearexcept(FE_ALL_EXCEPT);
        double from4 = DBL_MAX, to4 = nextafter(DBL_MAX, INFINITY);
        printf("The next representable double after %.2g (%a) is %.23f (%a)\n",
               from4, from4, to4, to4);
        if(fetestexcept(FE_OVERFLOW)) puts("   raised FE_OVERFLOW");
        if(fetestexcept(FE_INEXACT)) puts("   raised FE_INEXACT");
    } // end FENV_ACCESS block
}