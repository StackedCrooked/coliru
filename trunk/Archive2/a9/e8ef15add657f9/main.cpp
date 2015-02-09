#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 45

int main(void) 
{
    int *ptr = malloc(MAXLEN*sizeof(int));  // ALLOCATE MEM OF x NUM OF TYPES
    if (ptr == NULL) {        // CHECK IF MEMORY WAS ALLOCATED SUCCESSFULLY
        printf("Memory allocation failed for Object 'int' in file '%s' line: %d\n", __FILE__,__LINE__);
        exit(EXIT_FAILURE);
    } else {
        printf("Memory allocated for Object 'int' at address: %p\n", (void*)ptr);
    }
    for (int x = 0; x < MAXLEN; x++) {
        ptr[x] = 875 * x;
        printf("index: %04d | array data: %d\n", x, ptr[x]);
    }
    free(ptr); // DEALLOCATE MEMORY
    return EXIT_SUCCESS;
}
