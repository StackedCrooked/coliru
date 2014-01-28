#include <stdio.h>
#include <math.h>

int factorCount (long n)
{
    double square = sqrt (n);
    int isquare = (int) square;
    int count = isquare == square ? -1 : 0;
    int candidate;
    for (candidate = 1; candidate <= isquare; candidate ++)
        if (0 == n % candidate) count += 2;
    return count;
}

int main ()
{
    long triangle = 1;
    int index = 1;
    while (factorCount (triangle) < 1001)
    {
        index ++;
        triangle += index;
    }
    printf ("%ld\n", triangle);
}