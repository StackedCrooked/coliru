#include <vector>
#include <numeric>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>

// generate a vector containing n unique random integers in [ min_value, max_value ]
std::vector<int> unique_rand( std::size_t n, int min_value, int max_value )
{
    std::vector<int> vec( max_value - min_value + 1 ) ;

    // fill it up with min_value, min_value+1, min_value+2, ... max_value
    std::iota( std::begin(vec), std::end(vec), min_value ) ;

    // generate a random permutation of these numbers
    std::random_shuffle( std::begin(vec), std::end(vec) ) ;

    // resize to n elements (pick the first 'n' integers)
    vec.resize(n) ;

    return vec ;
}

int main()
{
    std::srand( std::time(nullptr) ) ;

    for( int i = 3 ; i < 10 ; ++i )
    {
        for( int r : unique_rand( 3, i, i*i ) ) std::cout << r << ' ' ;
        std::cout << '\n' ;
    }
}
