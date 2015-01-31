#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>

int sum_digits( int n )
{
    if( n < 0 ) return sum_digits( -n ) ;
    else if( n < 10 ) return n ;
    else return n%10 + sum_digits( n/10 ) ;
}

// http://en.cppreference.com/w/cpp/string/basic_string/to_string
// string comparisons are lexicographic
bool lex_compare( int a, int b )
{ return std::to_string(a) < std::to_string(b) ; }

// return true if a must appear before b in the sorted sequence
// see: http://en.cppreference.com/w/cpp/concept/Compare
bool compare( int a, int b ) // our predicate for sort
{
    const int sa = sum_digits(a) ;
    const int sb = sum_digits(b) ;
    if( sa == sb ) return lex_compare(a,b) ;
    else return sa < sb ;
}

int main()
{
    std::vector<int> seq { 6, 13, 36, 27, 12, 4, 123 } ;
    std::sort( std::begin(seq), std::end(seq), compare ) ;
    for( int v : seq ) std::cout << v << ' ' ;
    std::cout << '\n' ;
}
