#include <stdlib.h>
#include <stdio.h>

#define VERSION 1.0

int main()
{
    char string[100];
    
    sprintf(string, "Version: %f", VERSION);
    printf(string);
}
