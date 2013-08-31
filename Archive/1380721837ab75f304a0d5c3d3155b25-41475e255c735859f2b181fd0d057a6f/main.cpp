#include <stdio.h>

double metersToFeet(double meters)
{
    return meters / 0.3048;
}

int main()
{
    printf("%u\n", (unsigned char)(char)(45.72 / 0.3048));
    printf("%u\n", (unsigned char)(char)metersToFeet(45.72));
    return 0;
}