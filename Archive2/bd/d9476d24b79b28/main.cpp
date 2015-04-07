#include <stdio.h>
#include <stdlib.h>


void allocate_an_int(int **int_addr){
    *int_addr = malloc(sizeof(**int_addr)); // now we made the actual pointer to point to the freshly alocated memory
    **int_addr = 742015; //now the value is zero    
    printf("addr: %p value: %d\n", (void*)*int_addr, **int_addr);
}

int main(void){
    int *a = NULL;
    allocate_an_int(&a); // passing the address of the pointer
    printf("addr: %p value: %d\n", (void*)a, *a);
    free(a);
   
	
	return 0;
}