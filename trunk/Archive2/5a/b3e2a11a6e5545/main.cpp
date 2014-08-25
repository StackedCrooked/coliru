#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

int main()
{
    std::vector<int> seq { 1, 4, 5, 7, 4, 5, 8, 5, 9, 0, 6, 5, 3, 2, 5, 8 } ;
    for( int v : seq ) std::cout << v << ' ' ; std::cout << '\n' ;

    // remove all values equal to 5 (remove-erase idiom) O(N)
    seq.erase( std::remove( std::begin(seq), std::end(seq), 5 ), std::end(seq) ) ;
    for( int v : seq ) std::cout << v << ' ' ; std::cout << '\n' ;

    // remove all duplicates; may reorder sequence (remove-erase idiom) O(N log N)
    seq = { 1, 4, 5, 7, 4, 5, 8, 5, 9, 0, 6, 5, 3, 2, 5, 8 } ;
    std::sort( std::begin(seq), std::end(seq) ) ;
    seq.erase( std::unique( std::begin(seq), std::end(seq) ), std::end(seq) ) ;
    for( int v : seq ) std::cout << v << ' ' ; std::cout << '\n' ;

    // remove all duplicates; may not reorder sequence (remove-erase idiom) O(N) time, O(N) space
    seq = { 1, 4, 5, 7, 4, 5, 8, 5, 9, 0, 6, 5, 3, 2, 5, 8 } ;
    std::unordered_set<int> set ;
    auto iter = std::remove_if( std::begin(seq), std::end(seq),
                                [&set]( int v ) { return !set.insert(v).second ; } ) ;
    seq.erase( iter, std::end(seq) ) ;
    for( int v : seq ) std::cout << v << ' ' ; std::cout << '\n' ;
}
