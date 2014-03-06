#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
// on GNU gcc, compile with -std=c99 or -std=gnu99
int main() 
{
    char *str = malloc(20);
    char *tok = NULL;
    int len = 0;
 
    strcpy(str, "This is a string");
    len = strlen(str);
 
    printf("string before strtok(): %s\n", str);
    tok = strtok(str, " ");
    while (tok) {
        printf("Token: %s\n", tok);
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