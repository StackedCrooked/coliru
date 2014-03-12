#include <stdio.h>    /* printf             */
#include <stdlib.h>   /* calloc, free, exit */
 
int main () {
 
    /* Allocate an array of four integers. */
    /* Initialize all elements to 0.       */
    int *A = calloc(4,sizeof(int));
    if (A == NULL) {
       printf("calloc() failed in file %s at line # %d", __FILE__,__LINE__);
       exit(1);
    }
 
    /* Print one of the array elements. */
    printf("A[3] = %d\n", A[3]);
 
    /* Deallocate array A. */
    free(A);
    return 0;
}