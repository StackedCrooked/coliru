#include <iostream>
#include <vector>

int main()
{
    std::vector<int> frequency(10) ;

    unsigned int user_input = 3703537 ;

    while( user_input != 0  )
    {
        ++frequency[ user_input % 10 ] ;

        user_input /= 10 ;
    }

    for( int i : frequency ) std::cout << i << ' ' ;
    std::cout << '\n' ;
}
