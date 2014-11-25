#include <iostream>
#include <random> // http://coliru.stacked-crooked.com/a/38328294bdcab203
#include <ctime>

int main()
{
    // http://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine
    std::mt19937  rng( std::time(nullptr) ) ;

    // I want to get the numbers random from 100,000 to 999,999.
    // http://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
    std::uniform_int_distribution<int> distribution( 100000, 999999. ) ;

    for( int i = 0 ; i < 25 ; ++i )
    {
        const int pass = distribution(rng) ;
        std::cout << pass << '\n' ;
    }
}
