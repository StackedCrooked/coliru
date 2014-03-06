#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int (*sscanf_pfunc) ( const char * s, const char * format, ...);

enum T { a, b, c};
struct A{ enum T a; union { int a; char b;}  o; };

sscanf_pfunc pfn = &sscanf;

int main()
{
    const char* str = "hello"
                      "world";
    
    puts(str);
    //printf("%l", (long int)pfn);
}