#include <iostream>

void print_hex_digits( unsigned int n )
{
    static const unsigned int RADIX = 16 ;
    static const char hex_digits[] = "0123456789abcdef" ;

    char digit = hex_digits[ n % RADIX ] ;
    if( n >= RADIX ) print_hex_digits( n / RADIX ) ;
    std::cout << digit ;
}

void print_hex( unsigned int n )
{
    std::cout << "0x" ;
    print_hex_digits(n) ;
    std::cout << '\n' ;
}


int main()
{
    unsigned int numbers[] = { 0, 4095, 3058, 405, 1315, 3586, 3584, 12345678, 2882400018 } ; 
    for( unsigned int n : numbers ) print_hex(n) ;
}
