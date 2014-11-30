#include <iostream>
#include <string>
#include <cstdlib>

struct point
{
    std::string name ;
    int x ;
    int y ;

    int square_of_radius() const { return x*x + y*y ; }
};

point array[] = { { "B", 6, 8 }, { "A", 9, 12 }, { "D", 3, 4 } } ;
const int N = sizeof(array) / sizeof( array[0] ) ;

int compare( const void* pa, const void* pb )
{
    const int i = *static_cast< const int* >(pa) ;
    const int j = *static_cast< const int* >(pb) ;
    const int a = array[i].square_of_radius() ;
    const int b = array[j].square_of_radius() ;
    return (a>b) - (b>a) ;
}

int main()
{
    // indirect sort
    int indices[N] = { 0, 1, 2 } ;
    std::qsort( indices, N, sizeof( indices[0] ), compare ) ;

    for( int i : indices ) std::cout << array[i].name << ' ' << array[i].x << ' ' << array[i].y << '\n' ;
}
