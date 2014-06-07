#include <stdio.h>
#include <string.h>
 
int main(void)
{
    char str[] = "ABCDEFG";
    char *ps = memchr(str,'D',strlen(str));
    if (ps != NULL)
       printf ("search character found:  %s\n", ps);
    else
       printf ("search character not found\n");
 
    return 0;
}