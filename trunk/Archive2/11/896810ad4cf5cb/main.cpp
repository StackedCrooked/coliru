#include <iostream>
#include <cstring>

int main()
{

    int a[10];

    std::memcpy( a, ( const int[10] ){ 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 }, 
                    10 * sizeof( int) );

    for ( int x : a ) std::cout << x << ' ';
    std::cout << std::endl;
}
