#include <stdio.h>

size_t func()
{
    printf( "\nfunc()\n" ) ;
    return 10 ;
}

int main() {
    int x = 5;
    printf("%zu\n ",sizeof( char[x++]  ) ); 
    printf("%zu\n",sizeof( char[func()]  ) );
    
    printf( "%d\n", x ) ;
    
    printf("%zu\n",sizeof( int (*)[x++] ) ) ;
    printf( "%d\n", x ) ;
    return 0;
}