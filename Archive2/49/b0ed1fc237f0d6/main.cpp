#include <stdio.h>

void prev(int x)
{
    printf( "%d\n", x-1 );
}

void next(int x)
{
    printf( "%d\n", x+1 );
}

typedef void (*my_func_ptr_T)(int);

int main()
{
    my_func_ptr_T foo;
    
    foo = &prev;
    
    foo( 5 );

    return 0;
}