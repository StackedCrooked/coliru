#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int main(void)
{
    int len_A;
    int len_B;
    
    char A[] = "Take the test.";
    char *B = malloc(strlen(A) + 1);
    len_A = strlen(A);
    strcpy(B, A);
    len_B = strlen(B);
    A[0] = 'M';
    printf("A = %s\nB = %s\n", A, B);
    printf("%d\n",len_A);
    printf("%d\n",len_B);
    printf("%d\n",A[len_A]);
    printf("%d\n",B[len_B]);
    return 0;
}