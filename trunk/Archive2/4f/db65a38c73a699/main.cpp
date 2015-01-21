#include <stdio.h>
#define ROWS 2
#define COLS 2

int Sum2D(const int ar[][COLS], int rows);
int main(void)
{
    int array[ROWS][COLS]={{1,2},{3,4}};
    
    printf( "%d\n", Sum2D(array,ROWS) );
    
    return 0;
}

int Sum2D(const int ar[][COLS], int rows)
{
    int total=0;
    int i,j;
    for( i=0 ; i<rows ; i++ )
    {
        for( j=0 ; j<COLS ; j++ )
        {
            total+=ar[i][j];
        }
    }
    return total;
}