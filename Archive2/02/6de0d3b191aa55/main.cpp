#include <iostream>

int main()
{
    const unsigned int SZ = 1000001 ; // 0 - 10^6
    static unsigned int bucket[SZ] = {0} ;

    unsigned int number ;
    while( std::cin >> number ) ++bucket[ number%SZ ] ;

    for( unsigned int num = 0 ; num < SZ ; ++num )
    {
        const unsigned int cnt = bucket[num] ;
        for( unsigned int i = 0 ; i < cnt ; ++i ) std::cout << num << ' ' ;
    }
    std::cout << '\n' ;
}
