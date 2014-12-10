#include <stdio.h>

typedef struct pair pair ;
struct pair { int high ; int low ; } ;

pair make_pair( int a, int b ) { pair p = { a, b } ; return p ; }

#define ROWS 6
#define COLS 8

pair counts( const int array[ROWS][COLS], int row, int col )
{
    // invariant row in [1...ROWS-2], col in [1...COLS-2]
    int cnt_high = 0 ;
    int cnt_low = 0 ;

    for( int i = -1 ; i < 2 ; ++i ) for( int j = -1 ; j < 2 ; ++j )
    {
        cnt_high += array[row+i][col+j] > array[row][col] ? 1 : 0 ;
        cnt_low += array[row+i][col+j] < array[row][col] ? 1 : 0 ;
    }

    return make_pair( cnt_high, cnt_low ) ;
}

void peaks_and_valleys( const int array[ROWS][COLS] )
{
    for( int row = 1 ; row < (ROWS-1) ; ++row )
        for( int col = 1 ; col < (COLS-1) ; ++col )
        {
            const pair cnts = counts( array, row, col ) ;
            if( cnts.high == 8 )
                printf( "valley %d at %u,%u\n", array[row][col], row , col ) ;
            else if( cnts.low == 8 )
                printf( "valley %d at %u,%u\n", array[row][col], row , col ) ;
        }
}

int main()
{
    const int a[ROWS][COLS] =
    {
        { 25, 58, 63, 23, 21, 34, 21, 50 },
        { 32, 45, 43, 40, 41, 32, 30, 27 },
        { 34, 40, 38, 39, 36, 28, 30, 35 },
        { 40, 45, 42, 48, 32, 34, 29, 32 },
        { 39, 39, 40, 42, 47, 49, 27, 30 },
        { 31, 31, 31, 32, 32, 33, 44, 35 }
    };
    peaks_and_valleys(a) ;
}
