#include <iostream>
#include <algorithm>

void shell_sort( int array[], int n )
{
    static constexpr int gap_sequence[] = { 13, 9, 5, 2, 1 } ;

    // for (gap = n/2; gap > 0; gap /= 2)
    for( int gap : gap_sequence ) if( gap < n )
    {
        // for (i = gap; i < n; i++)
        for( int i = gap ; i < n; ++i )

            // for (j=i-gap; j>=0 && v[j]>v[j+gap]; j-=gap)
            for (int j = i-gap ; j >= 0 && array[j] > array[j+gap] ; j -= gap )
                /*
                    temp = v[j];
                    v[j] = v[j+gap];
                    v[j+gap] = temp;
                */
                std::swap( array[j], array[j+gap] ) ;
    }
}

void print( const int array[], int n )
{
    for( int i = 0 ; i < n ; ++i ) std::cout << array[i] << ' ' ;
    std::cout << '\n' ;
}

int main()
{
    int a[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 } ;
    constexpr int N = sizeof(a) / sizeof( a[0] ) ;

    std::random_shuffle( a, a+N ) ;
    print( a, N ) ;
    shell_sort( a, N ) ;
    print( a, N ) ;
}
