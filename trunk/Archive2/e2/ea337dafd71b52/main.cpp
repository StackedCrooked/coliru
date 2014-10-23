#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int main(void) 
{
    char *str = malloc(20);
    char *tok = NULL;
    int len = 0;
 
    strcpy(str, "This is a string");
    len = strlen(str);
 
    printf("string before strtok(): %s\n", str);
    tok = strtok(str, " ");
    while (tok) {
        printf("BLABLABLA: %s\n", tok);
        tok = strtok(NULL, " ");
    }
 
    printf("Print mangled string after strtok()\n");
    for (int i = 0; i < len; i++) {
        if (str[i] == '\0') {
            printf("'\\0'");
        } else {
            printf("%c", str[i]);
        }
    }
    printf("\n");
    free(str);
 
    return 0;
}