#include <array>
#include <iostream>

template < std::size_t... > struct pos {};

template < typename E, typename T > void assign( E& elem, pos<>, const T& v ) { elem = v ; }

template < typename E, std::size_t N, typename T, std::size_t FIRST, std::size_t... REST >
void assign( std::array<E,N>& array, pos<FIRST,REST...>, const T& v )
{ assign( array[FIRST], pos<REST...>{}, v ) ; }

template < typename, std::size_t... > struct NArray ;

template < typename T, std::size_t N > struct NArray<T,N> { using type = std::array<T,N> ; };

template < typename T, std::size_t FIRST, std::size_t... REST >
struct NArray<T,FIRST,REST...> { using type = std::array< typename NArray<T,REST...>::type, FIRST >; };

int main()
{
    NArray< int, 5, 6, 7, 8, 9 >::type a ;
    assign( a, pos< 3, 4, 2, 1, 5 >{}, 99 ) ;
    std::cout << a[3][4][2][1][5] << '\n' ;
}
