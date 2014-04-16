#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <iterator>
#include <random>
#include <ctime>
#include <cassert>

int main()
{
    using pair = std::pair< int, std::size_t > ; // int-value, std::size_t id

    constexpr std::size_t N = 1000000 ;
    constexpr int MIN = 4 ;
    constexpr int MAX = 10 ;

    std::vector<pair> seq(N) ;

    {
        std::mt19937 rng( std::time(nullptr) ) ;
        std::uniform_int_distribution<int> distr( MIN, MAX ) ;
        // monotonically increasing ids
        for( std::size_t i = 0 ; i < N ; ++i ) seq[i] = { distr(rng), i } ;
    }

    const auto cmp_val =  [] ( pair a, pair b ) { return a.first < b.first ; } ;
    std::stable_sort( std::begin(seq), std::end(seq), cmp_val ) ;

    assert( std::is_sorted( std::begin(seq), std::end(seq) ) ) ;
    // to test the stability of the sort, lexicographical comparison
    // of the pairs is adequate as the original ids were monotonically increasing

    // eqivalent to:
    for( int value = MIN ; value <= MAX ; ++value )
    {
        const auto eq_val = [value] ( pair p ) { return p.first == value ; } ;
        auto begin = std::find_if( seq.begin(), seq.end(), eq_val ) ;
        auto end = std::find_if( seq.rbegin(), seq.rend(), eq_val ).base() ;
        const auto cmp_id =  [] ( pair a, pair b ) { return a.second < b.second ; } ;
        assert( std::is_sorted( begin, end, cmp_id ) ) ;
    }
}
