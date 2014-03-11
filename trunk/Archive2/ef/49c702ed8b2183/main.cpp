#include <stdio.h>

int func()
{
    printf( "hello\n" ) ;
    
    return 1 ;
}

int
main()
{
    int arr[func()] ;
    int x = 1 ;
    
    printf( "%zu %d\n", sizeof( char[x++] ), x ) ;
    sizeof( char[func()]  ) ;
    printf( "%d\n", x ) ;
}
