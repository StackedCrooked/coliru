#include <iostream>
#include <cstdlib>
#include <ctime>

void srand_and_warmup( int seed = std::time( nullptr ), int discard = 16 )
{
    std::srand( seed ) ;
    for( int i = 0 ; i < discard ; ++i ) std::rand() ;
}

int main()
{
    srand_and_warmup() ;
    std::cout << std::rand() << '\n' ;
}
