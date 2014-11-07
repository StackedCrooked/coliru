#include <array>
#include <iostream>
#include <vector>

template < typename E, typename T > void assign( E& elem, std::vector<std::size_t>, const T& v ) { elem = v ; }

template < typename E, std::size_t N, typename T >
void assign( std::array<E,N>& array, std::vector<std::size_t> pos, const T& v )
{ assign( array[ pos.front() ], { pos.begin()+1, pos.end() }, v ) ; }

template < typename, std::size_t... > struct NArray ;

template < typename T, std::size_t N > struct NArray<T,N> { using type = std::array<T,N> ; };

template < typename T, std::size_t FIRST, std::size_t... REST >
struct NArray<T,FIRST,REST...> { using type = std::array< typename NArray<T,REST...>::type, FIRST >; };

int main()
{
    NArray< int, 5, 6, 7, 8, 9 >::type a ;
    assign( a, { 3, 4, 2, 1, 5 }, 99 ) ;
    std::cout << a[3][4][2][1][5] << '\n' ;
}
