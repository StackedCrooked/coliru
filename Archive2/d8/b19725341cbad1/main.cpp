#include <iostream>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <vector>

template < typename RANDOM_ACCESS_CONTAINER >
std::vector<std::size_t> order_indices_descending( const RANDOM_ACCESS_CONTAINER& seq )
{
    std::vector<std::size_t> indices( seq.size() ) ;
    std::iota( std::begin(indices), std::end(indices), 0 ) ; // fill with 0, 1, ..., n-1

    // indirect (descending) sort on indices
    std::sort( std::begin(indices), std::end(indices),
                [&seq] ( std::size_t i, std::size_t j ) { return seq[i] > seq[j] ; } ) ;

    return indices ;
}


int main()
{
    const std::vector<int> a { 4, 12, 434, 6, 24 } ;
    for( std::size_t pos : order_indices_descending(a) ) std::cout << pos << ' ' ;
    std::cout << '\n' ;
}
