#include <stdio.h>
#include <string.h>
 
#define LENGTH_STRING 20
 
int main(void)
{
    char source[LENGTH_STRING] = "Hello, world!";
    char target[LENGTH_STRING] = "";
    int integer[LENGTH_STRING / sizeof(int)] = {0};
    unsigned i;
    printf("source: %s\n", source);
    printf("target: %s\n", target);
    printf("integer: ");
    for (i = 0; i < sizeof(integer) / sizeof(integer[0]); ++i) {
        printf("%x ", integer[i]);
    }
    printf("\n========\n");
    memcpy(target, source, sizeof source);
    memcpy(integer, source, sizeof source);
    printf("source: %s\ntarget: %s\n", source, target);
    printf("source(hex): ");
    for (i = 0; i < sizeof(source) / sizeof(source[0]); ++i) {
        printf("%02x ", source[i]);
    }
    printf("\n");
    printf("integer(hex: %s-endian): ", integer[0] == 0x48656c6c ? "big" : "little");
    for (i = 0; i < sizeof(integer) / sizeof(integer[0]); ++i) {
        printf("%08x ", integer[i]);
    }
    printf("\n");
    return 0;
}