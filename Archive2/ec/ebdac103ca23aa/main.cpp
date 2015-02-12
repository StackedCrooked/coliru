#include <string.h>
#include <stdio.h>
 
int main(void)
{
    const char str[] = "How many characters does this string contain?";
 
    printf("without null character: %zu\n", strlen(str));
    printf("with null character: %zu\n", sizeof str);
}