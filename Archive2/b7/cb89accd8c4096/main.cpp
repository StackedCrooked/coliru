#include <string.h> 
#include <stdio.h>
 
int main(void) 
{
    char str[50] = "Hello!!)";
    char str2[50] = "World!";
    strcat(str, str2);
    strcat(str, " ...");
    strcat(str, " Goodbye World!");
    puts(str);
}