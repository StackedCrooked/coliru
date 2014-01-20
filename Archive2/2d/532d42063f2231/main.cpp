#include <random>
#include <algorithm>
#include <vector>
#include <set>
#include <iostream>
#include <iomanip>

// initialize the quasi rng
std::mt19937 initialize_twister( int seed )
{
    static constexpr std::size_t NDISCARD = 1024 ;

    std::minstd_rand lcg(seed) ;
    lcg.discard(NDISCARD) ;

    std::size_t seeds[ std::mt19937::state_size ] ;
    std::generate_n( seeds, std::mt19937::state_size, lcg ) ;

    std::seed_seq seed_sequence( std::begin(seeds), std::end(seeds) ) ;
    std::mt19937 twister { seed_sequence } ; // warm-up
    twister.discard(NDISCARD) ; // warm-up

    return twister ;
}

// generate uniformly distributed, unique, random numbers with the rng
std::vector<int> generate_unique( std::mt19937& rng, std::size_t n, int minv, int maxv )
{
    std::uniform_int_distribution<int> distr( minv, maxv ) ;
    std::set<int> set ;
    while( set.size() < n ) set.insert( distr(rng) ) ;
    return { set.begin(), set.end() } ;
}

// generate a new quasi random sequence of the numbers in seq (fisher yates shuffle)
std::vector<int> shuffle( std::vector<int>& seq )
{
    static std::mt19937 rng = initialize_twister(1000) ;
    std::shuffle( std::begin(seq), std::end(seq), rng ) ;
    return seq ;
}

int main()
{
    constexpr int N = 2 ;
    int seeds[N] { 5678, 111111 };

    std::vector<std::mt19937> rngs ; // quasi rngs
    for( int s : seeds ) rngs.push_back( initialize_twister(s) ) ;

    std::cout << "---------------------------------------------\n" ;
    for( auto& twister : rngs ) // for each rng
    {
        // generate 10 quasi random numbers uniformly distributed in [0,9999]
        std::vector<int> seq = generate_unique( twister, 10, 0, 9999 ) ;

        // print three quasi random sequences of these numbers
        for( int i = 0 ; i < 3 ; ++i )
        {
            shuffle(seq) ;
            for( int v : seq ) std::cout << std::setw(5) << v ;
            std::cout << '\n' ;
        }
        std::cout << '\n' ;
    }
}
