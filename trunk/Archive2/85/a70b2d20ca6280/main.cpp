#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int main(void)
{
    char A[] = "Take the test.";
    char *B = malloc(strlen(A) + 6);
    strcpy(B, A);
    A[0] = 'R';
    A[2] = 'p';
    printf("A = %s\nB = %s", A, B);
 
    return 0;
}