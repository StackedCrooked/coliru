#include <stdio.h>      /* printf             */
#include <stdlib.h>     /* free, malloc, exit */
 
int main() {
 
    /* Allocate an array with 100 integers. */
    int *A = malloc(100*sizeof(int));
    if (A == NULL) {        /* check that memory allocation occurred */
       printf("malloc() failed in file %s at line # %d", __FILE__,__LINE__);
       printf("***  PROGRAM TERMINATED  ***");
       exit(1);
    }
    printf("starting address of A:   %p\n", (void*)A);
 
    /* Deallocate array A. */
    free(A), A = NULL;
 
    /* Allocate an array with 100 doubles. */
    double *B = malloc(100*sizeof(double));
    if (B == NULL) {        /* check that memory allocation occurred */
       printf("malloc() failed in file %s at line # %d", __FILE__,__LINE__);  
       printf("***  PROGRAM TERMINATED  ***");
       exit(1);
    }
 
    /* Array B may have the same starting address that array A had. */
    printf("starting address of B:   %p\n", (void*)B);
 
    free(B);
    return 0;
}