#include <iostream>

// method one; works for integer types
void print_with_commas( unsigned long long n )
{
    const unsigned int THOUSAND = 1000 ;

    if( n < THOUSAND )
    {
        std::cout << n ;
    }
    else
    {
        int remainder = n % THOUSAND ;
        print_with_commas( n / THOUSAND ) ;
        std::cout << ',' << remainder ;
    }
}

int main()
{
    const int n = 123456789 ;
    print_with_commas(n) ; // 123,456,789
    std::cout << '\n' ;

    int m = -1234567 ;
    if( m < 0 )
    {
        std::cout << '-' ;
        m = -m ;
    }
    print_with_commas(m) ; // -1,234,567
    std::cout << '\n' ;
}
