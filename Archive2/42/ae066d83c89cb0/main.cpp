#include <stdio.h>
#include <string.h>

const char string1[6] = "140425";
const char* string2 = string1;

#define DATE "140425"

char date[6] = {DATE};


int main()
{    
    printf("%s\n", string1);
    printf("%s\n", string2);
    printf("%s\n", date);
}