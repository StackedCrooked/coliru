#include <iostream>
#include <unordered_map>

using pair_t = std::pair<int,int> ;

void increment_counts( std::unordered_map<int,int>& counts, pair_t interval )
{ for( int t = interval.first ; t <= interval.second ; ++t ) ++counts[t] ; } // O(M)

int main()
{
    pair_t intervals[] { {5,8}, {3,4}, {13,20}, {7,10} } ;

    std::unordered_map<int,int> counts ;
    for( const pair_t& interval : intervals ) // O(N)
        increment_counts( counts, interval ) ;

    int max_count = 0 ;
    for( const pair_t& p : counts ) // O(N)
        if( p.second > max_count ) max_count = p.second ;

    std::cout << "[ " ;
    for( const pair_t& p : counts ) // O(N)
        if( p.second == max_count ) std::cout << p.first << ' ' ;
    std::cout << "]\n" ;
}
