#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    char * a = NULL;
    char * b = NULL;
    char * c = NULL;
    
    char **arr = malloc(sizeof(char*)*3);
    c = malloc(sizeof(char)*4);
    strcpy(c,"abc");
    b = malloc(sizeof(char)*7);
    strcpy(b,"abcdef");
    a = malloc(sizeof(char)*7);
    strcpy(a,"itamar");
    
    arr[0] = a;     
    arr[1] = b;
    arr[2] = c;
    char k = *((*(arr+2))+2);
    printf("%c\n", k);
    printf("%s\n", arr[2]);
    
    printf("%c\n", arr[1][2]);
    
    free(a);
    free(b);
    free(c);
    free(arr);
    
	return (0);
}
