#include <stdio.h>
#include <math.h>
#include <float.h>

typedef double num;
 
int main(void)
{
    num numValue = 1e30; //LL;

    int nExponent = 0;

    frexp(
        numValue,
        & nExponent);

    // num: 1 bit - sign, 11 bit - exp, 52 - mantissa
    const int C_nExponentSizeInBits = 11;
    const int C_nMantissaSizeInBits = 52;
    const int C_nMaxExponent = 2 << C_nExponentSizeInBits;

    int nShiftedExponent =
        //GLimitWithAssert(
            nExponent - C_nMantissaSizeInBits;
            //-C_nMaxExponent,
            //C_nMaxExponent);

    num numError =
        ldexp(
            0.5,  // denormalized mode 1.^x == 0.5^(x-1)
            nShiftedExponent);


    printf("Error: %.2f \n", numError);
 
}