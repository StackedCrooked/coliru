#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char* x = (char*)malloc(32);
    strcpy(x+16, "Hello World!\n");
    free(x);
    puts(x+16);
}