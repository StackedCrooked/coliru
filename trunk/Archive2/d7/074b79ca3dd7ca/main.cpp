//#include <stdio.h>
#define MAX( a, b ) ( a > b ) ? (a) : (b)

int main()
{
    int x = 2, y = 2;

    if( MAX( ++x, y ) == x )
    {
        //printf( " %d is greater than %d ", x, y );
    }

    return 0;
}