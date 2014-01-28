#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>

template < typename RA_SEQUENCE > void sort( RA_SEQUENCE& seq )
{
    std::cout << "unordered: " ;
    for( const auto& v : seq ) std::cout << v << ' ' ;
    std::cout << '\n' ;

    std::sort( std::begin(seq), std::end(seq) ) ;

    std::cout << "   sorted: " ;
    for( const auto& v : seq ) std::cout << v << ' ' ;
    std::cout << "\n\n" ;
}


int main()
{
    int a[] = { 12, 45, 89, 23, 45, 65, 10, 98, 12, 34 } ;
    sort(a) ;

    std::string str = "managing a menagerie" ;
    sort(str) ;

    std::vector<std::string> vec = { "¿", "Could", "you", "use", "std::sort()", "for", "arrays", "?" } ;
    sort(vec) ;
}
