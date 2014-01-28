#include <iostream>

static const std::size_t ARRAY_SZ = 3 ;
extern int* const pointer ; // 1

extern int array[] ; // 2

extern int (&reference_to_array)[ARRAY_SZ] ; // 3

extern int array2[ARRAY_SZ] ; // 4

int main()
{
    for( std::size_t i = 0 ; i < ARRAY_SZ ; ++i ) std::cout << pointer[i] << ' ' ; // 1
    std::cout << '\n' ;

    for( std::size_t i = 0 ; i < ARRAY_SZ ; ++i ) std::cout << array[i] << ' ' ; // 2
    std::cout << '\n' ;

    for( int v : reference_to_array ) std::cout << v << ' ' ; // 3
    std::cout << '\n' ;

    for( int v : array2 ) std::cout << v << ' ' ; // 4
    std::cout << '\n' ;
}

int array[] = { 1, 2, 3 } ;

int* const pointer = array ;

int (&reference_to_array)[3] = array ;

int array2[] = { 1, 2, 3 } ;

