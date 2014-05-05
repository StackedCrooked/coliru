#include <iostream>

template < typename T >
T sum( const T array[], int pos_first_elem, int pos_last_elem )
{
    if( pos_first_elem == pos_last_elem ) // if there is only one element
        return array[pos_first_elem] ; // return that element

    else // if there are two or more elements
    {
        int pos_second_elem = pos_first_elem + 1 ;

        return array[pos_first_elem] + // return the first element plus
                sum( array, pos_second_elem, pos_last_elem ) ; // the sum of the remaining elements
    }
}

int main()
{
    const int SIZE = 10;
    const int ary[SIZE] = { 3, 4, 5, 6, 7, 8, 9, 10 , 11 , 12 };

    std::cout << sum( ary, 0, SIZE-1 ) << ' ' << (12*13) / 2 - 3 << '\n' ;
}
