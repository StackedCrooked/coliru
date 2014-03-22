#include <string.h>
#include <stdio.h>
 
int main()
{
    const char str[] = "How many characters contains this string?";
 
    printf("without null character: %d\n", (int)strlen(str));
    printf("with null character: %d\n", (int)sizeof(str));
 
    return 0;
}