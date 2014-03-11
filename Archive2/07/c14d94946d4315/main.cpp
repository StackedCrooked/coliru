#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iomanip>

int binary( int n )
{
    if( n == 0 ) return 0 ;
    else return binary(n/2) * 10 + n%2;
}

int main()
{
    std::cout<<"Converting decimal to binary\n\n" ;
    std::srand( std::time(nullptr) ) ;

    const std::size_t sz = 1 + std::rand()%5 ;
    std::vector<int> numbers(sz) ;
    for( int& v : numbers ) v = rand()%10;

    for( int n : numbers )
        std::cout << n << ' ' << std::setw(4) << std::setfill('0') << binary(n) << '\n' ;
}
