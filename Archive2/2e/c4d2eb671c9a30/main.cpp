#include <stdio.h>
#include <string.h>
 
int main(void)
{
    char str[] = "Hello, world!";
    char copy[40] = { 0 };
 
    /* no buffer overflow */
    strncpy(copy, str, sizeof(copy)-1);
    printf("%s\n", copy);
 
    /* copy partial amount of data */
    strncpy(copy, str, 3);
 
    /* add manually nullbyte.
     * comment it to see difference */
    copy[5] = '\0';
    printf("%s\n", copy);
 
    return 0;
}