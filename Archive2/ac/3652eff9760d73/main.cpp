#include <stdio.h>
#include <stdlib.h>
 
#define SIZE 7
 
int main(void)
{
    unsigned i = 0, array [SIZE];
 
    for( ; i < SIZE; ++i)
        array [i] = rand() % 2;
 
    printf("Array filled!\n");
 
    for (i = 0; i < SIZE; ++i)
        printf("%d ", array[i]);
 
    printf("\n");
 
    return EXIT_SUCCESS;
}