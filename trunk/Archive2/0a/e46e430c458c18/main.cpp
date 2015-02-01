#include <stdio.h>   
#include <stdlib.h> 
 
int main(void) 
{
    /* Allocate an array of four integers. */
    int *pa = malloc(4*sizeof(int));
    if (pa == NULL) {
       printf("malloc() failed in file %s at line # %d", __FILE__,__LINE__);
       exit(1);
    }
 
    /* Initialize array A with values. */
    for (int ndx=0; ndx < 4; ndx++)
        pa[ndx] = ndx;
 
    /* Print one of the array elements. */
    printf("pa[3] = %d\n", pa[3]);
 
    /* Deallocate array pa. */
    free(pa);
    return 0;
}