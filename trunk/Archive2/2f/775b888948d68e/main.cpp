#include <iostream>

int main()
{

    for( unsigned int decimal : { 0, 12, 32, 49, 124, 268, 532, 1028, 2197, 5238 } )
    {
        std::cout << decimal << ' ' ;

        unsigned long long binary = 0 ;
        unsigned int power = 0 ;

        while( decimal > 0 )
        {
            unsigned long long bit = decimal % 2 ;

            for( unsigned int i = 0 ; i < power ; ++i ) bit *= 10 ;
            binary += bit ;

            decimal /= 2 ;
            ++power ;
        }

        std::cout << binary << '\n' ;
    }
}
