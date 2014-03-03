#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <omp.h>

int main() {
    const int n = 256*8192*10;
    //const int n = 256*8192*100;
    double *A, *B;
    double dtime;
    posix_memalign((void**)&A, 64, n*sizeof(double));
    posix_memalign((void**)&B, 64, n*sizeof(double));
    //clock_t start = clock();
    dtime = omp_get_wtime();
    for (int i = 0; i < n; ++i) {
        A[i] = 0.1;
        B[i] = 0.0;
    }
    #pragma omp parallel for num_threads(8)
    for (int i = 0; i < n; ++i) {
        B[i] = exp(A[i]) + sin(B[i]);
    }
    double sum = 0.0;
    for (int i = 0; i < n; ++i) {
        sum += B[i];
    }
    dtime = omp_get_wtime() - dtime;
    printf("%f\n", dtime);
    //clock_t end = clock();
    //printf("%g %g\n", (double)(end - start)/CLOCKS_PER_SEC, sum);
    return 0;
}