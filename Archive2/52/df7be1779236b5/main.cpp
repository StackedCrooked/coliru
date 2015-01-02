#include <iostream>
#include <string>

// assumption: zero is repeated zero times (ie. ignored)
std::string repeat_digits( unsigned long long n )
{ return n==0 ? "" : repeat_digits(n/10) + std::string( n%10, n%10 + '0' ) ; }

int main()
{
    unsigned long long n ;
    std::cin >> n ;
    std::cout << repeat_digits(n) << '\n' ;
}
