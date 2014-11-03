#include <string.h>
#include <stdio.h>
 
int main(void) 
{
    const char* string = "Hello World!";
 
    //Matches
    int a = strcmp(string, "Hello World!");
    if (a == 0) {
        printf("Strings are matching.\n");
    }
 
    //Greater than
    int b = strcmp(string, "Hello");
    if (b >= 1) {
        printf("Left hand side is bigger than right hand side.\n");
    }
 
    //less than
    int c = strcmp(string, "Hello there world!");
    if (c <= -1) {
        printf("Left hand side is smaller than right hand side.\n");
    }
}