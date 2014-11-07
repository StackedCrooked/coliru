#include <set>
#include <iostream>
#include <algorithm>
#include <cmath>

double average( const std::multiset<int>& ms, int a, int b )
{
    if( a > b ) std::swap(a,b) ;

    const auto begin = ms.lower_bound(a) ;
    const auto end = ms.upper_bound(b) ;

    return begin == end ? std::nan("1") :
                          std::accumulate( begin, end, 0.0 ) / std::distance(begin,end) ;
}

int main()
{
    std::cout << average( { 5, 8, 3, 8, 5, 3, 2, 6, 8, 3, 1, 3, 5, 6, 5, 3 }, 4, 7 ) << '\n' ;
}
