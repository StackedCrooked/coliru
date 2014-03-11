#include <string.h>
#include <stdio.h>
 
int main()
{
    char *string_find = "abcde312$#@";
    char *low_alpha = "qwertyuiopasdfghjklzxcvbnm";
    printf("%lu", strspn(string_find, low_alpha));
    return 0;
}