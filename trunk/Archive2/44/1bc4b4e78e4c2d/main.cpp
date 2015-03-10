#include <iostream>

void printPowerOfTwoStars( int n )
{
    if( n == 0 ) std::cout << '*' ;

    else if( n > 0 )
    {
        printPowerOfTwoStars( n-1 ) ;
        printPowerOfTwoStars( n-1 ) ;
    }
}

int main()
{
    for( int i = 0 ; i < 7 ; ++i ) 
    {
        std::cout << i << "  " ;
        printPowerOfTwoStars(i) ;
        std::cout << '\n' ;
    }
}