#include <iostream>

int main()
{
    const int M = 3, N = 5 ;

    int a[M][N] = { { 0, 1, 2, 3, 4, }, { 5, 2, 6, 4, 7 }, { 6, 7, 5, 8, 9 } };
    
    for( int i = 0 ; i < M*N ; ++i )
    {
        for( int j = i+1 ; j < M*N ; ++j )
            if( a[0][i] == a[0][j] ) std::cout << a[0][i] << ' ' ; 
    }
    std::cout << '\n' ;
}
