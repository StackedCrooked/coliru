#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int main(void)
{
    char A[] = "Take the test.";
    char *B = malloc(strlen(A) + 1);
    strcpy(B, A);
    A[0] = 'M';
    printf("A = %s\nB = %s", A, B);
 
    return 0;
}