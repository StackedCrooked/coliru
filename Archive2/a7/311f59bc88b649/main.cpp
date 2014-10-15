#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
 char *remQuotes(char *);
 
int main(void) 
{
    char *str = malloc(200);
    char *tok = NULL;
 
    strcpy(str, "6 Jul '76,\"Bought 30 pixies\",\"I'm investing money!\",100.00");
 
    printf("string before strtok(): %s\n", str);
    tok = strtok(str, ",");
    while (tok) {
        printf("Token: |%s|\n", tok);
        tok = strtok(NULL, ",");
    }
 
    char *noQ = malloc(9);
    strcpy(noQ, remQuotes("\"Heyyy!\""));
    printf("\n\n\n|%s|", noQ);

    free(str);
 
    return 0;
}
char *remQuotes(char *s)
{
    char *buf = malloc((strlen(s) - 2) + 1);
    for (int i = 0; s[i]; i++)
        if (s[i] != '\"') {
            buf[i] = s[i];
            //printf("Copied %c into buf[%d]\n", s[i], i);
        }
    printf("%s", buf);
    return "";
}