#include <stdio.h>

int puts(const char* str)
{
    return printf("Hiya!\n");
}

int main()
{
    printf("Hello world.\n");
    return 0;
}