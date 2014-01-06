#include <stdio.h>
#include <string.h>
 
int main ()
{
    char str[] = "ghghghghghghghghghghgh";
    puts(str);
    memset(str,'a',5);
    puts(str);
    return 0;
}