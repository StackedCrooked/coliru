#include <iostream>
#include <random>
#include <ctime>
#include <cstdlib>
#include <algorithm>

static constexpr std::size_t N = 1024*1024*8 ;

std::vector<double> random_sequence()
{
    static std::mt19937 twister( std::time(nullptr) ) ;
    static std::normal_distribution<double> distr( 100, 25 ) ;
    static std::vector<double> seq(N) ;

    for( double& d : seq ) d = distr(twister) ;
    return seq ;
}

struct cpu_timer
{
    ~cpu_timer()
    {
        auto end = std::clock() ;
        std::cout << double( end - begin ) / CLOCKS_PER_SEC << " secs.\n" ;
    };

    const std::clock_t begin = std::clock() ;
};

template < typename SEQ > 
void bench_mark( SEQ& seq, const std::vector<double>& data, const char* desc )
{
    std::cout << desc << ": " ;
    cpu_timer timer ;
    std::copy( std::begin(data), std::end(data), std::begin(seq) ) ;
    std::sort( std::begin(seq), std::end(seq) ) ;
    for( auto& v : seq ) v = ( 100 - v ) * v ;
    std::sort( std::begin(seq), std::end(seq) ) ;
}

int main()
{
    const auto rand_seq = random_sequence() ;

    {
         std::vector<double> vector(N) ;
         bench_mark( vector, rand_seq, "vector" ) ;
    }

    {
         static double carray[N] ;
         bench_mark( carray, rand_seq, "c style array" ) ;
    }
}
