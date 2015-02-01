#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>
#include <tuple>
#include <limits>

std::pair<int,int> sum_and_num_digits( int n ) 
{
    if( n < 0 ) return sum_and_num_digits( -n ) ;
    else if( n < 10 ) return { n, 1 } ;
    else 
    {
        const auto p = sum_and_num_digits( n/10 ) ;
        return { p.first + n%10, p.second+1 }; 
    }
}

std::tuple<int,long long,int> make_key_tuple( int n ) // sum of digits, key for lex comparison, number
{
    if( n == 0 ) return std::make_tuple(0,0,0) ;
    
    const auto pair = sum_and_num_digits(n) ;
    long long lex_key = n ;
    static_assert( std::numeric_limits<long long>::digits10 > std::numeric_limits<int>::digits10, "" ) ;
    for( int i = pair.second ; i <= std::numeric_limits<int>::digits10 ; ++i ) lex_key *= 10 ;
    return std::make_tuple( pair.first, lex_key, n ) ;
}

int main()
{
    std::vector< std::tuple<int,long long,int> > seq ;
    for( int n : { 6, 13, 36, 27, 12, 4, 123 } ) seq.push_back( make_key_tuple(n) );
    std::sort( std::begin(seq), std::end(seq) ) ;
    for( const auto& tup : seq ) std::cout << std::get<2>(tup) << ' ' ;
    std::cout << '\n' ;
}
