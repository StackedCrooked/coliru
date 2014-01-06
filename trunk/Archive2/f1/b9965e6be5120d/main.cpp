#include <string.h>
#include <stdio.h>
 
int main()
{
    const char str[] = "Abc";
 
    printf("without null character: %lu\n", strlen(str));
    printf("with null character: %lu\n", sizeof(str));
 
    return 0;
}