#include <string.h>
#include <stdio.h>
 
int main()
{
    const char str[] = "How many chars contains this string?";
 
    printf("without null character: %d\n", strlen(str));
    printf("with null character: %d\n", sizeof(str));
 
    return 0;
}