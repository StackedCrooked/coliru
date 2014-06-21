#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
 
int main(void) 
{
    char str[1024];
    char *tok, *cp;
    strcpy(str, "This|is|a|string|||Yes?");
 
    printf("string before strtok(): %s\n", str);
    cp =  strdupa(str);
    tok = strsep(&cp, "|");
    while (tok) {
        printf("Token: %s\n", tok);
        tok = strsep(&cp, "|");
    }
    printf("\n"); 
    return 0;
}