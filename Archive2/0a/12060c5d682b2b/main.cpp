#include <stdio.h>
 
int main()
{
   printf("sizeof(_Complex float)       = %2zu\n", sizeof(_Complex float));
   printf("sizeof(_Complex double)      = %2zu\n", sizeof(_Complex double));
   printf("sizeof(_Complex long double) = %2zu\n", sizeof(_Complex long double));
 
    /* definition, initialization, and printing of _Complex variable */
    _Complex double z, zc;
    __real__ z = 1.0;  __imag__ z = 2.0;
    printf("%.1f%+.1fi\n", __real__ z, __imag__ z);
 
    /* complex assignment */
    zc = z;
 
    /* complex conjugate */
    __imag__ zc = -__imag__ z;
    printf("%.1f%+.1fi\n", __real__ zc, __imag__ zc);
 
    /* complex product */
    /* (a+bi)(a-bi) = a^2 + b^2 */
    z = z*zc;
    printf("%.1f%+.1fi\n", __real__ z, __imag__ z);
 
    return 0;
}