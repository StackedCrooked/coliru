#include <stdio.h>

enum blah
{
    A = (1 << 16),
    B = (1 << 17),
    C = (1 << 18),

    G = (1 << 20),

    TEST = (A | B | C , G)
} ;

int main()
{

    
    printf( "%d\n", TEST ) ;
}