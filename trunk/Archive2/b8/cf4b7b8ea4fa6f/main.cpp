#include <stdio.h>

int main( void ) 
{
             long long a = 834146832894220100LL;
    unsigned long long b = 834146832894220100ULL;

    printf( "%.16f\n%.16f\n",
        (( double )a / 1e+18),
        (( double )b / 1e+18)
    );

    getchar( );
    return 0;
}