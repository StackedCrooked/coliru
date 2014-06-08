#include <stdio.h>

// assumes that result can hold up to 'n' integers
// return the actual number of integers in result
size_t divisible_by_3_and_or_7( const int* numbers, size_t n, int* result ) 
{
    size_t cnt = 0 ;

    for( size_t i = 0 ; i < n ; ++i )
    {
        if( numbers[i]%3 == 0 || numbers[i]%7 == 0 )
        {
                result[cnt] = numbers[i] ;
                ++cnt ; 
        }
    }

    return cnt ; // number of integers divisible by 3 0r 7
}

int main()
{
    enum { N = 10 };
    int a[N] = { 11, 12, 13, 21, 14, 15, 42, 42, 16, 72 };

    int divisible[N] ;
    size_t cnt = divisible_by_3_and_or_7( a, N, divisible ) ;
    
    for( size_t i = 0 ; i < cnt ; ++i ) printf( "%d ", divisible[i] ) ;
    puts( "" ) ;
}
