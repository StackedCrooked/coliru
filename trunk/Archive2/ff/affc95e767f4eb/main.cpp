#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> next_palindrome( std::vector<int>& number )
{
    if( number.empty() ) return {1} ;

    auto mid = ( number.size() ) / 2 ;
    auto begin = number.begin() ;
    if( std::all_of( begin, begin+mid, [] ( int v ) { return v==9 ; } ) )
    {
        for( int& v : number ) v = 0 ;
        number.push_back(1) ;
        number.front() = 1 ;
        return number ;
    }

    auto iter = number.rbegin() + mid ;
    while( *iter == 9 ) { *iter = 0 ; ++iter ; }
    ++ *iter ;

    std::copy( number.rbegin()+mid, number.rend(), number.begin()+mid ) ;
    return number ;
}

int main()
{
    std::vector<int> number { 1, 2, 3, 4, 5, 6, 9, 5, 4, 3, 1, 9, 6, 4, 3, 7 } ;
    number.resize(60,9) ;

    for( int d : number ) std::cout << d ;
    std::cout << '\n' ;

    for( int d : next_palindrome(number) ) std::cout << d ;
    std::cout << '\n' ;
}
