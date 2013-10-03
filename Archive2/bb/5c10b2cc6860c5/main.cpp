#include <stdio.h>
#include <stdlib.h>

void parseNumber(const char* s)
{
    char *ptr;
    long num = strtol(s, &ptr, 10);
    if (*ptr == '\0' && num >= 1 && num <= 1000000) {
        printf("yay, number is valid!\n");
    }
    else {
        printf("oh noo!!! not is not valid!\n");
    }  
}

int main(int argc, char** argv)
{
  parseNumber("0");
  parseNumber("1000");
  parseNumber("100000000");
}
