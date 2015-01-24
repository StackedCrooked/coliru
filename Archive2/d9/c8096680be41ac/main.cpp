#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    double x = 5;
    double y = 6;
    double a = exp(3 * x) * exp(4 * y);

    printf("%f\n", a);
    return 0;
}