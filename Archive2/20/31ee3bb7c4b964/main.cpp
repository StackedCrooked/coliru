#include <iostream>
#include <random>
#include <ctime>
#include <algorithm>

// initialize the rng with a seed
// for the same seed, will generate the same sequence of pseudo random numbers
std::mt19937 initialize_twister( std::size_t seed )
{
    static constexpr std::size_t NDISCARD = 1024 ;

    std::minstd_rand lcg(seed) ;
    lcg.discard(NDISCARD) ;

    std::size_t seeds[ std::mt19937::state_size ] ;
    std::generate_n( seeds, std::mt19937::state_size, lcg ) ;

    std::seed_seq seed_sequence( std::begin(seeds), std::end(seeds) ) ;
    std::mt19937 twister { seed_sequence } ; // warm-up
    twister.discard(NDISCARD) ; // more warm-up

    return twister ;
}

struct object
{
    object() : twister( initialize_twister( rand_dev() ) ) {}
    object( std::size_t seed ) : twister( initialize_twister(seed) ) {}
    
    int next() { return distribution(twister) ; }
    std::mt19937 twister ;
    
    static std::random_device rand_dev ;
    static std::uniform_int_distribution<int> distribution ;
};

std::random_device object::rand_dev ;
std::uniform_int_distribution<int> object::distribution( 1000, 9999 ) ;

int main()
{
    {
        object a ; // random seed
        for( int i = 0 ; i < 10 ; ++i ) std::cout << a.next() << ' ' ; 
        std::cout <<  "  (random seed)\n" ;
    }
    
    {
        object b(2345) ; //  seed is 2345
        for( int i = 0 ; i < 10 ; ++i ) std::cout << b.next() << ' ' ; 
        std::cout << "  (seeded with 2345)\n" ;
    }
    
    {
        object c(777777) ; //  seed is 77777
        for( int i = 0 ; i < 10 ; ++i ) std::cout << c.next() << ' ' ; 
        std::cout << "  (seeded with 77777)\n" ;
    }
    
    {
        object d(2345) ; //  seed is 2345 (generates the same sequence as object b) 
        for( int i = 0 ; i < 10 ; ++i ) std::cout << d.next() << ' ' ; 
        std::cout << "  (seeded with 2345)\n" ;
    }
}

