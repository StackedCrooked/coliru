
#include <math.h>
#include <stdio.h>

int main()
{
    volatile float s = 0.0001;
    volatile float f = 0.00105;
    volatile float f1 = floorf(f / s) * s;
    printf("%.30f", f1);
}