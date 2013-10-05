#include <iostream>
#include <algorithm>
#include <numeric>
#include <iterator>

int main()
{
    const int a[] = { 4, 12, 434, 6, 24 } ;
    for( int v : a ) std::cout << v << ' ' ;
    std::cout << '\n' ;

    std::size_t indices[ sizeof(a) / sizeof(a[0]) ] ;
    std::iota( std::begin(indices), std::end(indices), 0 ) ; // fill with 0, 1, ..., n-1

    // indirect (descending) sort on indices
    std::sort( std::begin(indices), std::end(indices),
                [&a] ( std::size_t i, std::size_t j ) { return a[i] > a[j] ; } ) ;

    for( std::size_t pos : indices ) std::cout << pos << ' ' ;
    std::cout << '\n' ;

}
