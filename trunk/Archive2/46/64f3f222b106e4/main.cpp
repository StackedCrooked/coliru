#include <iostream>

int main()
{
    const int NDIGITS = 30 ;
    int number[NDIGITS] = {0} ;

    for( int i = 0 ; i<NDIGITS ; ++i )
    {
        char digit ;
        const char zero = '0' ;
        const char nine = '9' ;
        std::cin >> digit ;
        if( digit >= zero && digit <= nine ) number[i] = digit - zero ;
        else std::cerr << digit << " is not a decimal digit (set to zero)\n" ;
    }

    for( int v : number ) std::cout << v ;
    std::cout << '\n' ;
}
