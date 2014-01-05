#include <set>
#include <iostream>

template< typename T, typename U >
void merge( std::set<T>& bigger, const std::set<U>& smaller )
{
    // invariant: largest element of smaller is smaller than the smallest element of bigger
    for( auto iter = smaller.rbegin() ; iter != smaller.rend() ; ++iter )
        bigger.emplace_hint( bigger.begin(), *iter ) ;
        // http://en.cppreference.com/w/cpp/container/set/emplace_hint

}

int main ()
{
    std::set<int> big { 10, 11, 12, 13, 14 } ;
    const std::set<long> small { 0, 1, 2, 3, 4 } ;
    
    merge( big, small ) ;
    
    for( int v : big ) std::cout << v << ' ' ;
    std::cout << '\n' ;
}
