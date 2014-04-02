#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 
int main()
{
    printf("%d\n", abs(+3));
    printf("%d\n", abs(-3));
 
    /* Two’s complement arithmetic cannot represent the   */
    /* absolute value of the most negative integer value. */
    printf("%+d\n", INT_MIN);
    printf("%+d\n", INT_MAX);   
    printf("%+d\n", abs(INT_MIN));
 
    return 0;
}