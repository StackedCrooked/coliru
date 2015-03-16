#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
    std::srand( std::time(0) ) ;

    for( int i = 0 ; i < 10 ; ++i )
    {
        int amount_won = 2 ;

        while( std::rand() % 1000 < 500  ) // half the time, till a head comes up
        {
            amount_won += 2 ;
            std::cout << 'T' ;
        }

        std::cout << "H You win $" << amount_won << ".00\n" ;
    }

}
