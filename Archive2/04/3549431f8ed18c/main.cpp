#include <stdio.h>
#include <stdlib.h>
 
#define SIZE 8
 
int main(void)
{
    unsigned i = 0, array [SIZE];
 
    do
    {
        array [i] = rand() % 2;
        ++i;
    } while (i < SIZE);
 
    printf("Array filled!\n");
 
    i = 0;
    do
    {
        printf("%d ", array[i]);
        ++i;
    } while (i < SIZE);
 
    printf("\n");
 
    return EXIT_SUCCESS;
}