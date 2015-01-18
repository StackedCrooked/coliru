#include <stdio.h>   
#include <stdlib.h> 
 
int main(void) 
{
    /* Allocate an array of four integers. */
    int *pa = malloc(5*sizeof(int));
    if (pa == NULL) {
       printf("malloc() failed in file %s at line # %d", __FILE__,__LINE__);
       exit(1);
    }
 
    /* Initialize array A with values. */
    for (int ndx=0; ndx < 5; ndx++)
        pa[ndx] = ndx;
 
    /* Print one of the array elements. */
    printf("pa[4] = %d\n", pa[4]);
 
    /* Deallocate array pa. */
    free(pa);
    return 0;
}