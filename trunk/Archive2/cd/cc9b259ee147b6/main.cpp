#include <iostream>

// returns index to 1st even number in partitioned array
unsigned int evensToRight( int a[], unsigned int sz )
{
    unsigned left = 0, right = sz-1;
    while( left < right )
    {
        //find first even
        while( left<right && a[left]%2 != 0 ) ++left;
        // find last odd
        while( left<right && a[right]%2 == 0 ) --right;

        if( left<right )// swap the elements
        {
            int temp = a[left];
            a[left] = a[right];
            a[right] = temp;
        }
    }
    return left;
}

void print_partition( const int a[],  unsigned int n,  unsigned int pos )
{
    for( unsigned int i = 0 ; i < n ; ++i )
    {
        if( i == pos ) std::cout << " <-->  " ;
        std::cout << a[i] << ' ' ;
    }
    std::cout << '\n' ;
}

int main()
{
    int array[] = { 10, 13, 17, 11, 14, 15, 12, 19, 18, 16 };
    const unsigned int N = sizeof(array) / sizeof( array[0] ) ;
    const unsigned int pos = evensToRight( array, N ) ;
    print_partition( array, N, pos ) ;

    int array2[] = { 8, 6, 7, 4, 5, 2 };
    const unsigned int N2 = sizeof(array2) / sizeof( array2[0] ) ;
    const unsigned int pos2 = evensToRight( array2, N2 ) ;
    print_partition( array2, N2, pos2 ) ;
}
