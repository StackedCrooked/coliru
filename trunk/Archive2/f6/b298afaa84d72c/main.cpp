#include <iostream>
#include <vector>

int main()
{
    std::vector<int> seq { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 } ;
        
    // remove odd elements as we are iterating
    for( auto iter = std::begin(seq) ; iter != std::end(seq) ;  )
    {
        if( *iter % 2 ) 
        {
            std::cout << "removing " << *iter << '\n' ;
            iter = seq.erase(iter) ; // returns an iterator to the elment immediately after 
                                     // the element that was removed (or end if there is none).
        }
        else ++iter ; // not erased; so increment iter
    }
        
    for( int v : seq ) std::cout << v << ' ' ;
    std::cout << '\n' ;
}
