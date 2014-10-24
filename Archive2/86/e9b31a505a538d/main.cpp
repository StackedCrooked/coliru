#include <stdio.h>
#include <omp.h>

int main() {
    int i;
    omp_set_num_threads(4);
    puts("schedule(static,1)");
    #pragma omp parallel for schedule(static,1) 
    for(i=0; i<16; i++) { 
        printf("t %d, i %d\n", omp_get_thread_num(), i);
    }

    puts("for(i = omp_get_thread_num(); i<16; i+=4");
    #pragma omp parallel private(i)
    {
        for(i = omp_get_thread_num(); i<16; i+=4) {
            printf("t %d, i %d\n", omp_get_thread_num(), i);
        }
    }
    return 0;
}