#include <iostream>

int main()
{

    for( unsigned int decimal : { 0, 12, 32, 49, 124, 268, 532, 1028, 2197, 5238 } )
    {
        std::cout << decimal << ' ' ;

        unsigned long long binary = 0 ;
        unsigned long long multiplier = 1 ;

        while( decimal > 0 )
        {
            unsigned long long bit = decimal % 2 ;
            binary += bit * multiplier ;

            decimal /= 2 ;
            multiplier *= 10 ;
        }

        std::cout << binary << '\n' ;
    }
}
