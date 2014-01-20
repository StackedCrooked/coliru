#include <vector>
#include <cassert>
#include <algorithm>
#include <iostream>

template < typename T, typename V >
bool binary_search( const std::vector< std::vector<T> >& outer, const V& v )
{
    static const auto lt = [] ( const std::vector<T>& seq, const T& v )
    { assert( !seq.empty() ) ; return seq.back() < v ; };

    const auto iter = std::lower_bound( outer.begin(), outer.end(), v, lt ) ;
    return iter != outer.end() && std::binary_search( iter->begin(), iter->end(), v ) ;
}

int main()
{
    const std::vector< std::vector<int> > v2=
    {
        { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 },
        { 10, 11, 12, 13, 13, 13, 16, 17, 18, 19 },
        { 19, 19, 19, 20, 21, 22, 23, 27, 28, 29 },
        { 50, 51, 52, 53, 54, 55, 56, 57, 58, 59 }
    };

    std::cout << std::boolalpha ;
    for( int i : { -6, 0, 5, 9, 10, 19, 25, 38, 59, 86 } )
        std::cout << i << ' ' << binary_search( v2, i ) << '\n' ;
}
