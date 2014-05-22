/*
inline int sum(int a, int b) {
  return (a + b);
}
 
int c = sum(1, 4);
// If the compiler inlines the function the compiled code will be the same as writing:
int c = 1 + 4;
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
/* int sum (int a, int b) __attribute__ ((noinline)); */
 
static inline
int sum (int a, int b)
{
  return a+b;
}
 
int main(void)
{
    const int SIZE = 100000;
    int X[SIZE],Y[SIZE],A[SIZE];
    int i,j;
    for (i=0;i<SIZE;++i) {
        X[i] = rand();
        Y[i] = rand();
    }
 
    clock_t t = clock();   /* start clock */
    for (i=0;i<5000;++i) {
        for (j=0;j<SIZE;++j)
            A[j] = sum(X[j],Y[j]);
    }
    t = clock()-t;         /* stop clock  */
 
    printf("Time used: %f seconds\n", ((float)t)/CLOCKS_PER_SEC);
    printf("%d\n", A[0]);
    return EXIT_SUCCESS;
}