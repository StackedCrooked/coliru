#include <stdio.h>

int main()
{
    const char *s = "hello";    // Not permitted to modify the string "hello"
    char *const t = "world";    // Not permitted to modify the pointer t

  printf( "%s\n", t ) ;
}