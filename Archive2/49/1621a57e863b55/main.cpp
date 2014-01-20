#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>

int main()
{
    // http://en.cppreference.com/w/cpp/numeric/random/srand
    std::srand( std::time(nullptr) ) ;

    // generate and print 100 random numbers aaproximately uniformly distributed in [0,1]
    // http://en.cppreference.com/w/cpp/numeric/random/rand
    for( int i = 0 ; i < 10 ; ++i )
    {
        for( int j = 0 ; j < 10 ; ++j )
            std::cout << std::fixed << std::setw(5)
                       << std::rand() / double(RAND_MAX) << ' ' ;
        std::cout << '\n' ;
    }
}
