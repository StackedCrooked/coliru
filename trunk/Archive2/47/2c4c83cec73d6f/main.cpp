#include <vector>
#include <algorithm>
#include <iostream>
 
int main()
{
    std::vector<int> seq { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 } ;
    const auto print = [&seq] () -> std::ostream& { for( int v : seq ) std::cout << v << ' ' ;  return std::cout << '\n' ; } ;
    print() ;

    // remove an element from a sequence container without changing the sequence of the other elements
    // use erase
    seq.erase( seq.begin() + 5 ) ;
    print() << '\n' ;

    // remove an range of (consecutive) elements from a sequence container without changing the sequence of the other elements
    // use erase
    seq = { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 } ;
    print() ;
    seq.erase( seq.begin()+3, seq.begin()+7 ) ;
    print() << '\n' ;

    // remove some elements from a sequence container without changing the sequence of the other elements
    // use erase-remove idiom: https://en.wikipedia.org/wiki/Erase-remove_idiom
    // example: erase all even numbers from the sequence
    seq = { 20, 21, 22, 23, 24, 25, 26, 27, 28, 29 } ;
    print() ;
    seq.erase( std::remove_if( seq.begin(), seq.end(), []( int v ) { return v%2 == 0 ; } ), seq.end() ) ;
    print() << '\n' ;
}