#include <random>
#include <ctime>
#include <iostream>

int main()
{
    const int max_digits = 12 ; // max digits in the random number generated

    // compute max value
    long long max_value = 1 ;
    for( int i = 0 ; i < max_digits ; ++i ) max_value *= 10 ;
    max_value -= 1 ;

    // random number generator seeded with time
    // http://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine
    std::mt19937 rng( std::time(0) ) ;

    // pseudo random integers uniformly distributed in [ -max_value, max_value ]
    // http://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
    std::uniform_int_distribution<long long> distr( -max_value, max_value ) ;

    for( int i = 0 ; i < 20 ; ++i )
    {
        const long long random_number = distr(rng) ; // generate a random number
        std::cout << random_number << '\n' ;
    }
}
