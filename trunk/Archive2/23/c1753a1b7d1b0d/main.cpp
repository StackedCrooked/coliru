#include <omp.h>
#include <stdio.h>
//#include <stdlib.h>

#define RNG_MOD 0x80000000
int state;

int rng_int(void);
double rng_doub(double range);

int main() {
    int i, numIn, n;
    double x, y, pi;

    n = 1<<30;
    numIn = 0;

    #pragma omp threadprivate(state)
    #pragma omp parallel private(x, y) reduction(+:numIn) 
    {
        
        state = 25234 + 17 * omp_get_thread_num();
        #pragma omp for
        for (i = 0; i <= n; i++) {
            x = (double)rng_doub(1.0);
            y = (double)rng_doub(1.0);
            //printf("%f %f\n", x, y);
            if (x*x + y*y <= 1) numIn++;
        }
    }
    pi = 4.*numIn / n;
    printf("asdf pi %f\n", pi);
    return 0;
}

int rng_int(void) {
   // & 0x7fffffff is equivalent to modulo with RNG_MOD = 2^31
   return (state = (state * 1103515245 + 12345) & 0x7fffffff);
}

double rng_doub(double range) {
    return ((double)rng_int()) / (((double)RNG_MOD)/range);
}
