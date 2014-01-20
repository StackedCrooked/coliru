#include <random>
#include <ctime>
#include <iostream>
#include <iomanip>

int main()
{
    // http://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine
    std::mt19937 rng( std::time(nullptr) ) ;

    // generate and print 100 random numbers uniformly distributed in [0,1)
    // http://en.cppreference.com/w/cpp/numeric/random/uniform_real_distribution
    std::uniform_real_distribution<double> distribution( 0, 1 ) ;
    for( int i = 0 ; i < 10 ; ++i )
    {
        for( int j = 0 ; j < 10 ; ++j )
            std::cout << std::fixed << std::setw(5) << distribution(rng) << ' ' ;
        std::cout << '\n' ;
    }
}
