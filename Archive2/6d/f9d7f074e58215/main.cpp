#include <omp.h>
#include <cstdio>

int main()
{

    int nthreads, tid;

#pragma omp parallel private(tid)
    {

        tid = ::omp_get_thread_num();
        printf("Hello World from thread = %d\n", tid);

        /* Only master thread does this */
        if (tid == 0) {
            nthreads = ::omp_get_num_threads();
            printf("Number of threads = %d\n", nthreads);
        }

    } /* All threads join master thread and terminate */
}
