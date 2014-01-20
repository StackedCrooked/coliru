#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

double hamming_distance(int* a, int*b, int n) {
    double dist = 0;
    for(int i=0; i<n; i++) {
        if (a[i] != b[i]) dist++;
    }
    return dist/n;
}

double hamming_distance_fix(int* a, int*b, int n) {
    int disti = 0;
    for(int i=0; i<n; i++) {
       disti += (a[i] != b[i]);
    }
    return 1.0*disti/n;
}

double hamming_distance_fix_omp(int* a, int*b, int n) {
    int disti = 0;
    #pragma omp parallel for reduction(+:disti)
    for(int i=0; i<n; i++) {
       disti += (a[i] != b[i]);
    }
    return 1.0*disti/n;
}

int main() {
    const int n = 1<<16;
    const int repeat = 10000;
    int *a = new int[n];
    int *b = new int[n];
    for(int i=0; i<n; i++) 
    { 
        a[i] = rand()%10;
        b[i] = rand()%10;
    }

    double dtime, dist;
    dtime = omp_get_wtime();
    for(int i=0; i<repeat; i++) dist = hamming_distance(a,b,n);
    dtime = omp_get_wtime() - dtime;
    printf("dist %f, time (s) %f\n", dist, dtime);
    
    dtime = omp_get_wtime();
    for(int i=0; i<repeat; i++) dist = hamming_distance_fix(a,b,n);
    dtime = omp_get_wtime() - dtime;
    printf("dist %f, time (s) %f\n", dist, dtime);
    
     dtime = omp_get_wtime();
    for(int i=0; i<repeat; i++) dist = hamming_distance_fix_omp(a,b,n);
    dtime = omp_get_wtime() - dtime;
    printf("dist %f, time (s) %f\n", dist, dtime);
   

}