#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N       500
#define CSIZE   1
#define nthread 2

int pi() {
    int chunk;
    float pi = 0;
    
    chunk = CSIZE;
    omp_set_num_threads(nthread);
    
    #pragma omp parallel
    {
        if (omp_get_num_threads() == 0)
        {
            printf("Number of threads = %d\n", omp_get_num_threads());
        }
    
        printf("Thread %d starting...\n", omp_get_thread_num());
        int i;
        #pragma omp for schedule(dynamic, chunk) reduction(+:pi)
        for (i = 0; i < N; i++)
        {
            if (i % 2 == 0)
                pi +=  4.0f/(2*i+1);
            else
                pi += -4.0f/(2*i+1);
        }
    }
    printf("%f\n", pi);
    
    return EXIT_SUCCESS;
}

int main() {
    pi();
}