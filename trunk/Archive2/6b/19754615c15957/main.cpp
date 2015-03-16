#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

int main()
{
    std::srand( std::time(0) ) ;
    const int N = 10 ;

    double total = 0 ;

    for( int i = 0 ; i < N ; ++i )
    {
        int amount_won = 2 ; // amount won is at least two (for the terminating H)

        while( std::rand() % 1000 < 500  ) // half the time, till a head comes up
        {
            amount_won += 2 ; // add $2 for every T
            std::cout << 'T' ;
        }

        std::cout << "H You win $" << amount_won << ".00\n" ;

        total += amount_won ;
    }

    std::cout << "\naverage: $" << std::fixed << std::setprecision(2) << total / N << '\n' ;

}
