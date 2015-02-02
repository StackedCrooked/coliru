#include <string.h> 
#include <stdio.h>
 
int main(void) 
{
    char* str = "Hello ";
    char* str2 = "World!";
    strcat(str, str2);
    
    puts(str);
}