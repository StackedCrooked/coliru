#include <iostream.h>

// returns -1 if the value is not found
int search( const int numbers[], int size, int numberToSearch )
{
    int location = -1;
    // iterate through the array
    for( int i = 0; i < size; ++i ) {
        if( numbers[ i ] == numberToSearch ) { // if same
            location = i; // assign i to location
            break; // break
        }
    }
    return location; // return the location
}

int main()
{
    const int N = 5;
    int ids[ N ] = { 128, 43, 434, 343, 115 }; // array of numbers

    int i = search( ids, N, 434 );

    if( i == -1 ) {
        cout << "Not Found!\n";
    } else {
        cout << "Location in array is : " << i+1 << '\n';
    }
}