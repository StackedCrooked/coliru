#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
/* on GNU gcc, compile with -std=c99 or -std=gnu99 */
int main() 
{
    char *str = malloc(20);
    char *tok = NULL;
    int len = 0;
    int i;
 
    strcpy(str, "This_is_a_string");
    len = strlen(str);
 
    printf("string before strtok(): %s\n", str);
    tok = strtok(str, "_");
    while (tok) {
        printf("Token is : %s\n", tok);
        tok = strtok(NULL, "_");
    }
    
    /* len = strlen(str); */
    printf("Print mangled string after strtok()\n");
    for (i = 0; i < len; i++) {
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