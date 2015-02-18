#include <stdio.h>
#include <float.h>

int main()
{
    printf("\nThe size of the smallest non-zero value of type long double is %.3Le", LDBL_MIN);
    printf("\nThe size of the largest value of type long double is %.3Le\n", LDBL_MAX);
}
