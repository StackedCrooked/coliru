#include <iostream>
#include <algorithm>
#include <utility>
#include <iterator>

int main()
{
    using pair = std::pair<int,char> ;

    pair a[] = { { 6, 'a' },  { 5, 'b' },  { 4, 'c' }, { 5, 'd' },
                 { 4, 'e' }, { 6, 'f' }, { 5, 'g'}, { 4, 'h' } } ; // int-value, char-id

    for( auto p : a ) std::cout << '{' << p.first << ',' << p.second << "} " ;
    std::cout << '\n' ;

    const auto cmp =  [] ( pair a, pair b ) { return a.first < b.first ; } ;

    std::stable_sort( std::begin(a), std::end(a), cmp ) ;
    for( auto p : a ) std::cout << '{' << p.first << ',' << p.second << "} " ;
    std::cout << '\n' ;
}
