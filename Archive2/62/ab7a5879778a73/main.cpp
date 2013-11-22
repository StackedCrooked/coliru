#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
 
int main(int argc, char *argv[])
{
    printf("Welcome to %s\n", argv[0]);
    printf("Called with %u arguments\n", argc - 1);
 
    char buffer[L_tmpnam] = {'\0'};
    tmpnam(buffer);
    printf(buffer);
    printf("\n");
 
    printf("Goodbye!\n");
    exit(EXIT_SUCCESS);
}