#include <stdio.h>
#include <stdlib.h>
 
/* static storage duration */
int A;       // uninitialized global variable; this system initializes with zero
int B = 9;   // initialized global variable
 
int main(void)
{
    printf("&A = %p\n", (void*)&A);
    printf("&B = %p\n", (void*)&B);
 
    /* automatic storage duration */
    int A = 1;   // hides global A
    printf("&A = %p\n", (void*)&A);
 
    /* static storage duration */
    static int B=1; // hides global B
    printf("&B = %p\n", (void*)&B);
 
    /* allocated storage duration */
    int *ptr_1 = (int*)malloc(sizeof(int));   /* start allocated storage duration */
    printf("address of int in allocated memory = %p\n", (void*)ptr_1);
    free(ptr_1);                              /* stop allocated storage duration  */
 
    return 0;
}