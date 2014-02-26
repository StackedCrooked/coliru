#include <stdio.h>

int func()
{
    printf("hello world\n" ) ;
    return 1 ;
}

int main()
{
    int x = 1 ;
    printf( "x = %d\n", x ) ;
    printf( "sizeof( char[x++] ) = %zu\n", sizeof( char[x++] ) ) ;
    printf( "x = %d\n", x ) ;
    printf( "sizeof( char[x++] ) = %zu\n", sizeof( char[func()] ) ) ;
}
