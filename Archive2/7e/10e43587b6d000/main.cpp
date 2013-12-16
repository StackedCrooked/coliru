#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>

std::vector<int> next_palindrome( std::vector<int> number )
{
    if( number.empty() || number.front() == 0 ) return {1} ;

    auto mid = number.size() / 2  ;
    std::vector<int> left { number.begin(), number.begin() + mid + number.size()%2 } ;

    if( std::all_of( left.begin(), left.end(), []( int v ) { return v==9 ; } ) )
    {
        for( int& v : number ) v = 0 ;
        number.push_back(1) ;
        number.front() = 1 ;
        return number ;
    }

    else if( std::lexicographical_compare( left.rbegin(), left.rend(),
                                               number.begin()+mid, number.end() ) )
    {
        auto iter = left.rbegin() ;
        while( *iter == 9 ) ++iter ;
        ++ *iter ;
    }

    std::copy( left.begin(), left.end(), number.begin() ) ;
    std::copy( left.begin(), left.end(), number.rbegin() ) ;
    return number ;
}

std::vector<int> random_number()
{
    static std::mt19937 twister( std::time(nullptr) ) ;

    static std::uniform_int_distribution<> digit(0,9) ;
    static std::uniform_int_distribution<> non_zero_digit(1,9) ;
    static std::uniform_int_distribution<> rand_size( 10, 60 ) ;
    std::vector<int> result( 1, non_zero_digit(twister) ) ;
    std::size_t sz = rand_size(twister) ;
    while( result.size() < sz ) result.push_back( digit(twister) ) ;

    return result ;
}

void print( const std::vector<int>& number )
{
    auto mid = number.size() / 2 ;

    for( std::size_t i = 0 ; i < mid ; ++i ) std::cout << number[i] ;
    std::cout << ' ' ;

    if( number.size() % 2 ) std::cout << number[mid++] << ' ' ;

    for( std::size_t i = mid ; i < number.size() ; ++i ) std::cout << number[i] ;
    std::cout << '\n' ;
}

int main()
{
    std::vector< std::vector<int> > test { std::vector<int>(12,9) } ;
    while( test.size() < 10 ) test.emplace_back( random_number() ) ;

    for( const auto& number : test )
    {
        print(number);
        print( next_palindrome(number) ) ;
        std::cout << '\n' ;
    }
}
