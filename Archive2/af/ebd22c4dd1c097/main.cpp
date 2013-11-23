#include <string.h> 
#include <stdio.h>
 
int main() 
{
    char str[50] = "Hello ";
    char str2[50] = "World!";
    strcat(str, str2);
    strncat(str, " Goodbye World!", 3);
    puts(str);
}