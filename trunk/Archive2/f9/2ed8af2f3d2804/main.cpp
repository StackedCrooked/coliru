#include <string.h>
#include <stdio.h>
 
int main(void)
{
    const char str[] = "How many characters contains this string?";
 
    printf("without null character: %zu\n", strlen(str));
    printf("with null character: %zu\n", sizeof(str));
 
    return 0;
}