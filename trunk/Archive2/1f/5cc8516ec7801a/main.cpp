#include <stdio.h>
#include <math.h>

float floatMod(float a, float b)
{
    return (a - b * floor(a/b));
}

int main()
{
    printf("%f\n", fmodf(18.5f, 4.2f));
    printf("%f\n", floatMod(18.5f, 4.2f));
}
