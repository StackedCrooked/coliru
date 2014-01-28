#include <math.h>
#include <stdio.h>
#include <time.h>
 
// the function f() does some time-consuming work
void f()
{
    volatile double d; // we dont want subsequent computation to be optimized out
    for (int n=0; n<10000; ++n)
       for (int m=0; m<10000; ++m)
           d += d*n*m;
}
 
int main ()
{
    clock_t t = clock();
    f();
    t = clock() - t;
    printf("Time used: %f seconds\n",((float)t)/CLOCKS_PER_SEC);
 
    return 0;
}