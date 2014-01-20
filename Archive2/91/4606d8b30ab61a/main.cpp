#include <iostream>

// in an array of integers 'a' of size 'sz' (sz>0),
// find and return the position of the smallest element
std::size_t position_of_smallest_element( const int a[], std::size_t sz )
{
    std::size_t pos_smallest = 0 ;

    for( std::size_t i = 1 ; i < sz ; ++i )
        if( a[pos_smallest] > a[i] ) pos_smallest = i ;

    return pos_smallest ;
}

// in an array of integers 'a' of size 'sz' (sz>0),
// bring the smallest element to the front
void bring_smallest_element_to_front( int a[], std::size_t sz )
{
    std::size_t pos_smallest = position_of_smallest_element( a, sz ) ;

    // swap smallest element with the one at the front (at position zero)
    int temp = a[0] ;
    a[0] = a[pos_smallest] ;
    a[pos_smallest] = temp ;
}

// sort an array of integers 'a' of size 'sz'
void sort( int a[], std::size_t sz )
{
    if( sz < 2 ) return ; // only zero or one element, nothing to be done

    // bring the smallest element of the array to the front
    bring_smallest_element_to_front( a, sz ) ;

    // a[0] already contains the smallest elenent of the array
    // all that remains to be done is: sort the remaining elements of the array
    // the remaining elents start at a+1, and have a size of sz-1
    sort( a+1, sz-1 ) ;
}

int main()
{
    int a[] = { 6, 2, 8, 3, 7, 6, 1, 9, 7, 4, 2, 5, 3 } ;
    for( int v : a ) std::cout << v << ' ' ;
    std::cout << '\n' ;

    sort( a, sizeof(a) / sizeof( a[0] ) ) ;

    for( int v : a ) std::cout << v << ' ' ;
    std::cout << '\n' ;
}
