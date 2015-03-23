#include <stdio.h>
#include <string.h>
 
int main(void)
{
    char str[] = "ghghghghghghghghghghgh";
    puts(str);
    memset(str,'a',100);
    puts(str);
}