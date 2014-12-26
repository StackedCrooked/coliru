#include <stdio.h>

int call (int *);

int main (void)
{
    int v=11;
    printf ("\nResult is:  %d\n", (call(&v)));
    return 0;
}

int call (int *v)
{
    *v*=*v++;
    return  (++*--v);
}