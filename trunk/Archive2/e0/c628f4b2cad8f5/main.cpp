#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

int main()
{
    {
        std::vector<int> seq { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 } ;
        for( int v : seq ) std::cout << v << ' ' ;
        std::cout << '\n' ;

        // erase odd numbers from the vector
        for( auto iter = std::begin(seq) ; iter != std::end(seq) ; )
        {
            if( *iter%2 ) iter = seq.erase(iter) ; // erase if odd
            else ++iter ;
        }

        for( int v : seq ) std::cout << v << ' ' ;
        std::cout << '\n' ;
    }

    {
        std::vector<int> seq { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 } ;
        for( int v : seq ) std::cout << v << ' ' ;
        std::cout << '\n' ;

        // erase odd numbers from the vector

        // step 1. move all odd numbers to the end of the vector
        // http://en.cppreference.com/w/cpp/algorithm/remove
        auto iter = std::remove_if( std::begin(seq), std::end(seq),
                                      []( int i ) { return i%2 == 1 ; } ) ;

        // step 2. iter 'points' to the first odd number, erase everything from there on
        seq.erase( iter, std::end(seq) ) ;

        for( int v : seq ) std::cout << v << ' ' ;
        std::cout << '\n' ;
    }

    {
        std::vector<int> seq { 0, 1, 1, 2, 3, 3, 3, 3, 4, 4, 5, 6, 6 } ;
        for( int v : seq ) std::cout << v << ' ' ;
        std::cout << '\n' ;

        // erase adjacent duplicates from the vector

        // step 1. move duplicate adjacent elements to the end of the vector
        // http://en.cppreference.com/w/cpp/algorithm/unique
        auto iter = std::unique( std::begin(seq), std::end(seq) ) ;

        // step 2. iter 'points' to the first of the duplicates, erase everything from there on
        seq.erase( iter, std::end(seq) ) ;

        for( int v : seq ) std::cout << v << ' ' ;
        std::cout << '\n' ;
    }

}
