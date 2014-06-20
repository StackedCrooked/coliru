#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int main(void) 
{
    char str[1024];
    char *tok = NULL;
    strcpy(str, "This is a string");
 
    printf("string before strtok(): %s\n", str);
    tok = strtok(str, " ");
    while (tok) {
        printf("Token: %s\n", tok);
        tok = strtok(NULL, " ");
    }
    printf("\n"); 
    return 0;
}