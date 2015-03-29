#include <iostream>

// return the index if the value is found; -1 if value isn't found
int find( const int array[], int array_size, int pos, int value_to_find )
{
    // if we have reached the end of the array and not found the value
    if( pos >= array_size ) return -1 ;

    // if the value we are looking for is at index pos
    else if( array[pos] == value_to_find ) return pos ; // found at array[pos]

    // recursively call find for positions on the right, starting at pos+1
    else return find( array, array_size, pos+1, value_to_find ) ; 
}

int main()
{
    const int N = 10 ;
    const int a[N] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    std::cout << find( a, N, 0, 0 ) << '\n' // 0
              << find( a, N, 0, 5 ) << '\n' // 5
              << find( a, N, 0, 9 ) << '\n' // 9
              << find( a, N, 0, 25 ) << '\n' ; // -1
}
