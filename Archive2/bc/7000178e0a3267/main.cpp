#include <stdio.h>
#include <string.h>
 
#define LENGTH_STRING 20
 
int main() 
{
    char source[LENGTH_STRING] = "Hello, world!";
    char target[LENGTH_STRING] = "";
    int integer[LENGTH_STRING / 4] = {0};
    int i = 0;
    printf("source: %s\n", source);
    printf("target: %s\n", target);
    printf("integer: ");
    for (i = 0; i < sizeof(integer) / sizeof(integer[0]); ++i) {
        printf("%x ", integer[i]);
    }
    printf("\n");	
    printf("========\n");
 
    /* length + 1 for the string's end-char '\0' */
    memcpy(target, source, strlen(source) + 1); 
    memcpy((char *)integer, source, strlen(source));
    printf("source: %s\n", source);
    printf("target: %s\n", target);
    printf("source(hex): ");
    for (i = 0; i < sizeof(source) / sizeof(source[0]); ++i) {
        printf("%2x ", source[i]);
    }
    printf("\n");
    printf("integer(hex: little-endian): ");
    for (i = 0; i < sizeof(integer) / sizeof(integer[0]); ++i) {
        printf("%x ", integer[i]);
    }
    printf("\n");
    return 0;
}