#include <string.h>
#include <stdio.h>
 
int main(void)
{
    char *string_find = "abcde312$#@";
    char *low_alpha = "qwertyuiopasdfghjklzxcvbnm";
    printf("%zu", strspn(string_find, low_alpha));
    return 0;
}