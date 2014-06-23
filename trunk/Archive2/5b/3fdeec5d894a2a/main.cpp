#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
 
// the function f() does some time-consuming work
void f()
{
    volatile double d=0.0; // we don't want subsequent computation to be optimized out
    for (int n=0; n<10000; ++n)
       for (int m=0; m<10000; ++m)
           d += d*n*m;
}
 
int main(void)
{
    clock_t t = clock();
    if (t == ((clock_t)-1))
    {
       fprintf(stderr,"clock() failed in file %s at line # %d\n", __FILE__,__LINE__-3);
       exit(EXIT_FAILURE);
    }
 
    f();
    t = clock() - t;
    printf("Time used: %f seconds\n",((float)t)/CLOCKS_PER_SEC);
 
    return 0;
}