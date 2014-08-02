#include <iostream>
#include <cstdlib>
#include <ctime>

void my_srand( int seed = std::time( nullptr ), int discard = 20 )
{
    std::srand( seed ) ;
    for( int i = 0 ; i < discard ; ++i ) std::rand() ;
}

int main()
{
    my_srand() ;
    std::cout << std::rand() << '\n' ;
}
