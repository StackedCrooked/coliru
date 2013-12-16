#include <omp.h>
#include <stdio.h>
//#include <stdlib.h>

#define RNG_MOD 741025

int rng_int(int state) {
    return (state = (1366 * state + 150889) % RNG_MOD);
}

double rng_doub(double range, int state) {
    return ((double)state) / (double) ((RNG_MOD - 1)/range);
}

int main() {
    int i, numIn, n;
    int state;
    double x, y, pi;

    n = 10000000;
    numIn = 0;

    #pragma omp parallel private(state, x, y) reduction(+:numIn) 
    {
        
        state = 25234 + 17 * omp_get_thread_num();
        #pragma omp for
        for (i = 0; i <= n; i++) {
            state = rng_int(state);
            x = (double)rng_doub(1.0, state);
            state = rng_int(state);
            y = (double)rng_doub(1.0, state);
            if (x*x + y*y <= 1) numIn++;
        }
    }
    pi = 4.*numIn / n;
    printf("asdf pi %f\n", pi);
    return 0;
}