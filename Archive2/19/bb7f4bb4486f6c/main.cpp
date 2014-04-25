#include <iostream>
#include <list>
#include <set>
#include <numeric>

int main()
{
    std::list< std::set<int> > seq { { 0, 25, 7 }, { 1, 6, 12 }, { 20, 21, 22 }, { 1, 3, 7, 8 }, { 5, 6, 7 } } ;
    
    const auto print = [] ( const std::set<int>& set ) 
                          { std::cout << "[ " ; for( int v : set ) std::cout << v << ' ' ; std::cout << "]\n" ; } ;
        
    // as we iterate, remove sets which sum up to 19
    for( auto iter = std::begin(seq) ; iter != std::end(seq) ;  )
    {
        const auto& set = *iter ;
        if( std::accumulate( set.begin(), set.end(), 0 ) == 19 ) 
        {
            std::cout << "removing set " ;
            print(set) ;
            
            iter = seq.erase(iter) ; // returns an iterator to the elment immediately after 
                                     // the element that was removed (or end if there is none).
        }
        else ++iter ; // not erased; so increment iter
    }
     
    std::cout << "\nthe sequence now contains:\n" ;
    for( const auto& set : seq ) print(set) ;
}
