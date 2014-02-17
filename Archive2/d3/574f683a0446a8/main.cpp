#include <iostream>
#include <iomanip>

void swap( int a[], int i, int j ) // swap elements a[i], a[j]
{
    int temp = a[i] ;
    a[i] = a[j] ;
    a[j] = temp ;
}

void print_array( const int a[], int n )
{
    static int cnt = 0 ;
    std::cout << std::setw(3) << ++cnt << ". " ;
    for( int i = 0 ; i < n ; ++i ) std::cout << a[i] << ' ' ;
    std::cout << '\n' ;
}

// array 'a' of size 'n', permute range starting at position 'from'
void permute( int a[], int n, int from = 0 )
{
    // if the entire range has been permuted, print the permutation
    if( from == n ) return print_array( a, n ) ;

    // else
    for( int i = from ; i < n ; ++i ) // repeat: for each element in the range to permute
    {
        swap( a, from, i ) ; // make this element the head (at position from)
        permute( a, n, from+1 ) ; // form all permutations of the tail (starting at from+1)
        swap( a, from, i ) ; // restore the original positions
    }
}

int main()
{
    int a[] = { 1, 2, 3, 4 } ;
    std::cout << "permutations\n--------------\n" ;
    permute( a, sizeof(a) / sizeof( a[0] ) ) ;
}
