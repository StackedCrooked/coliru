#include <stdio.h>

enum { MAX_SIZE = 100 } ;

typedef struct array array ;
struct array
{
    size_t actual_size ;
    int values[MAX_SIZE] ;
};

array divisible_by_3_and_or_7( const int* numbers, size_t n ) 
{
    array result ; 
    
    size_t cnt = 0 ;
    for( size_t i = 0 ; i < n ; ++i )
    {
        if( numbers[i]%3 == 0 || numbers[i]%7 == 0 )
        {
            if( cnt < MAX_SIZE ) 
            {
                result.values[cnt] = numbers[i] ;
                ++cnt ; 
            }
            else break ; // no more space
        }
    }
    result.actual_size = cnt ;
    
    return result ;
}

int main()
{
    int a[10] = { 11, 12, 13, 21, 14, 15, 42, 42, 16, 72 };
    
    array divisible = divisible_by_3_and_or_7( a, 10 ) ;
    for( size_t i = 0 ; i < divisible.actual_size ; ++i ) printf( "%d ", divisible.values[i] ) ;
    puts( "" ) ;
}
