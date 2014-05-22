#include <string.h>
#include <stdio.h>
 
int main(void)
{
    char str[] = "Hello World";
    char *ptr = strchr(str, 'W');
    printf("%s", ptr);
}