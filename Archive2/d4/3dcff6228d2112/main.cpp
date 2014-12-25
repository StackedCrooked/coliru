#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

float rand_spot()
{
    const int x = std::rand() % 10000 ;
    return x/100.0f - 50.0f ;
}

int main()
{
    std::srand( std::time(0) ) ;
    std::cout << std::fixed << std::setprecision(1) << std::showpos << std::internal ;
    for( int i = 0 ; i < 10 ; ++i )
    {
        for( int i = 0 ; i < 10 ; ++i ) std::cout << std::setw(5) << rand_spot() << "  " ;
        std::cout << '\n' ;
    }
}
