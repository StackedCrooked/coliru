#include <iostream>
#include <utility>

template< typename LAST > void printf( LAST&& last ) { std::cout << last << '\n' ; }

template< typename FIRST, typename... REST > void printf( FIRST&& first, REST&&... rest ) 
{ 
    std::cout << first << ' ' ;
    printf( std::forward<REST>(rest)... ) ;
}

int main()
{
    int i = 8 ;
    printf( i, i+8, "hello", "world", '!', 9999 ) ;
}
