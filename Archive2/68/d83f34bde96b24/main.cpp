#include <stdio.h>
#include <string.h>

int main()
{
    enum { N = 4, M = 5, SZ = N*M };

    const int one_d[SZ] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 } ;

    int two_d[N][M] ;
    memcpy( two_d[0], one_d, SZ * sizeof(int) ) ;

    for( int i = 0 ; i < N ; ++i )
    {
       for( int j = 0 ; j < M ; ++j ) printf( "%d ", two_d[i][j] ) ;
       puts( "" ) ;
    }
}
