#include <iostream>

int main()
{
    const int N = 10 ;
    const int a[N] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 } ;

    int i = 0 ; // initialize counter
    while( i < N ) // check condition
    {
        std::cout << a[i] << ' ' ; // do our stuff for this iteration
        ++i ; // increment counter
    }
    std::cout << '\n' ; // do this when the lop exits

    i = 0 ; // initialize counter
    if( i < N ) do // check condition at the beginning
    {
        std::cout << a[i] << ' ' ; // do our stuff for this iteration
        ++i ; // increment counter
    } while( i < N ) ; // check condition at the end of each iteration
    std::cout << '\n' ; // do this when the lop exits

    for( int i = 0 /* initialize counter */ ; i < N  /* check condition */ ; ++i /* increment counter */ )
        std::cout << a[i] << ' ' ; // do our stuff for this iteration
    std::cout << '\n' ; // do this when the lop exits

    // http://www.stroustrup.com/C++11FAQ.html#for
    for( int v : a ) // for each integer in the array
       std::cout << v << ' ' ; // do our stuff for this iteration
    std::cout << '\n' ; // do this when the lop exits

    std::cout << "a[5] == " << a[5] << '\n' ;
    std::cout << "a[5] == " << *(a+5) << '\n' ;
    std::cout << "a[5] == " << 5[a] << '\n' ;
    std::cout << "a[5] == " << *(5+a) << '\n' ;

    int x = 23 ;
    int y = 23 ;

    if( x == y ) std::cout << "x is equal to y\n" ;

    ++x ; y += 1 ;
    if( !(x<y) && !(y<x) ) std::cout << "x is still equal to y\n" ;

    x = x+1 ; y++ ;
    if( !(x>y) && !(y>x) ) std::cout << "x is still equal to y\n" ;

    x -= 1 ; y += -1 ;
    if( !( x!=y ) ) std::cout << "x is still equal to y\n" ;

}
