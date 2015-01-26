#include <iostream>

constexpr unsigned long long MOD = 1000000007 ;

unsigned long long modular_sqare( unsigned long long n )
{
    n %= MOD ;

    static_assert( ( (MOD*MOD) / MOD ) == MOD, "integer overflow" ) ;
    // note: if this static assertion fails,
    // see: https://en.wikipedia.org/wiki/Modular_arithmetic#Example_implementations

    return ( n * n ) % MOD ;
}

int main()
{
    const unsigned long long test_data[] =
    {
        5351871996120528,
        2248813659738258,
        2494359640703601,
        6044763399160734,
        3271269997212342,
        4276346434761561,
        2372239019637533,
        5624204919070546,
        9493965694520825,
        8629828692375133
    };

    for( auto n : test_data ) std::cout << modular_sqare(n) << '\n' ;
}
