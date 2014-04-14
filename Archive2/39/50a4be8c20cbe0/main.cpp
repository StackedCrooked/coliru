#include <stdio.h>
#include <time.h>
 
/* Function f() performs some time-consuming work. */
void f()
{
    /* Keyword "volatile" tells the compiler not to assume that this function */
    /* is the only part of the system that could change variable d.           */
    volatile double d;
    int m,n;
    for (n=0; n<10000; ++n)
       for (m=0; m<10000; ++m)
           d += d*n*m;
}
 
int main ()
{
    int i;
    clock_t t = clock();
    for (i=0;i<3;++i) f();
    t = clock() - t;
    printf("Time used: %f seconds\n", ((float)t)/CLOCKS_PER_SEC);
    return 0;
}