#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip> // for setw
using namespace std;

const int N = 5 ; // compile-time constant

typedef int array_type[N] ; // 'array_type' is an array of N int or int[N]

// these functions recieve a pointer to the first element of an array
// the type of the element is an array of N int int[N]
// the number of elements is num_elems
void FillArray( array_type* first, int num_elems ) ;
void PrintArray( const array_type* arr, int num_elems ) ;

int main()
{
    int arr[N][N];
    srand(time(0));

    array_type* first = arr ; // 'arr' is implicilly converted to a pointer
                              // 'first' points to the first element of 'arr'
                              // that element is an array of N int or int[N]

    // fill the array; pass pointer to first element and number of elememts
    FillArray( first, N ) ;

    // print the array; pass pointer to first element and number of elememts
    // 'arr' decays to a pointer to the first element
    // sizeof(arr) gives the size of 'arr' (bytes)
    // sizeof( arr[0] ) gives the size of the first element of 'arr'
    // sizeof(arr) / sizeof( arr[0] ) gives the number of elements
    PrintArray( arr, sizeof(arr) / sizeof( arr[0] ) ) ;

    {
        std::cout << "\n------------------------------------------\n\n" ;
        const int M = 8 ;
        int another_array[M][N] ;
        FillArray( another_array, M ) ;
        PrintArray( another_array, M ) ;
    }
}

void FillArray( array_type* first, int num_elems )
{
    for( int r=0; r < num_elems ; ++r )
    {
        array_type& row = first[r] ; // the element (row) at position r

        for( int c=0; c < N;  ++c )
        {
            int& e = row[c] ; // the integer at position (col) c
            e = (rand() % 998) + 44;
        }
    }
}

void PrintArray( const array_type* arr, int num_elems )
{
    for( int r=0; r < num_elems ; ++r )
    {
        for( int c=0; c < N;  ++c )
        {
            cout << setw(6) << arr[c][r];
        }
        cout << '\n';
    }
}
