#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <iterator>

std::vector<int>& next_palindrome( std::vector<int>& number )
{
    if( number.empty() || number.front() == 0 ) return number = {1} ;

    auto begin = number.begin() ;
    auto end = number.begin() + number.size() / 2 + number.size()%2 ;
    std::reverse_iterator<decltype(end)> rbegin(end) ;
    std::reverse_iterator<decltype(end)> rend(begin) ;

    if( std::all_of( begin, end, []( int v ) { return v==9 ; } ) )
    {
        for( int& v : number ) v = 0 ;
        number.push_back(1) ;
        number.front() = 1 ;
        return number ;
    }

    else if( std::equal( rbegin, rend, begin+number.size()/2 ) ||
              std::lexicographical_compare( rbegin, rend,
                                               begin+number.size()/2, number.end() ) )
    {
        auto iter = rbegin ;
        while( *iter == 9 ) { *iter = 0 ; ++iter ; }
        ++ *iter ;
    }

    std::copy( begin, end, number.rbegin() ) ;
    return number ;
}

int main()
{
    {
        std::vector<int> test[]
        {
          std::vector<int>(30,9), { 1, 2, 3, 4, 5, 6, 7, 8 },
          { 6, 2, 3, 7, 5, 6, 7, 8 }, { 6, 9, 9, 9, 9, 9, 9, 9 },
          { 1, 2, 3, 4, 5, 0, 7, 8, 9 }, { 6, 2, 3, 4, 5, 6, 7, 8, 9 },
          { 5, 9, 9, 9, 6, 7, 7, 8, 9 }, { 1, 2, 3, 4, 5, 4, 3, 2, 1 },
          { 1, 2, 3, 4, 5, 5, 4, 3, 2, 1 }, { 8, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
          { 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8 }
        };

        for( auto& number : test )
        {
            for( int v : number ) std::cout << v ;
            std::cout << '\n' ;
            for( int v : next_palindrome(number) ) std::cout << v ;
            std::cout << "\n\n" ;

        }
    }

    static std::mt19937 twister( std::time(nullptr) ) ;
    static std::uniform_int_distribution<> digit(0,9) ;
    static std::uniform_int_distribution<> non_zero_digit(1,9) ;

    constexpr std::size_t NDIGITS = 1000 * 1000 * 10 ; // 10 million digits
    std::vector<int> big( 1, non_zero_digit(twister) ) ;
    double ticks = 0 ;

    for( int i = 0 ; i < 10 ; ++i )
    {
        big.resize(1) ;
        while( big.size() < NDIGITS ) big.emplace_back( digit(twister) ) ;

        auto begin = std::clock() ;
        int x = next_palindrome(big).back() ;
        auto end = std::clock() ;
        if( x < 25 ) ticks += (end-begin) ;
    }
    std::cout << ticks / CLOCKS_PER_SEC << " seconds\n" ;
}
