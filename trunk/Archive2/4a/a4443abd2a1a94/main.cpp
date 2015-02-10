#include <iostream>
#include <random>
#include <algorithm>
#include <iterator>

int main()
{
    int a[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 } ;

    // http://en.cppreference.com/w/cpp/numeric/random
    static std::mt19937 rng( std::random_device{}() ) ; // random number engine

    for( int i = 0 ; i < 5 ; ++i )
    {
        // http://en.cppreference.com/w/cpp/algorithm/random_shuffle
        std::shuffle( std::begin(a), std::end(a), rng ) ;
        for( int v : a ) std::cout << v << ' ' ;
        std::cout << '\n' ;
    }
}
