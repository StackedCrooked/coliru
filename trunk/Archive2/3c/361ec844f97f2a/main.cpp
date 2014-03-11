#include <string.h>
#include <stdio.h>
 
int main() 
{
    const char* string = "Hello World!";
    const int size = strlen(string);
    //Matches
    int a = strncmp(string, "Hello World!");
    if (a == 0) {
        printf("The 5 first char of each string are matching.\n");
    }
 
    //Greater than
    int b = strncmp(string, "Hello");
    if (b >= 1) {
        printf("Left hand side is bigger than right hand side.\n");
    }
 
    //less than
    int c = strcmp(string, "Hello there world!");
    if (c <= -1) {
        printf("Left hand side is smaller than right hand side.\n");
    }
}