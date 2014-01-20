#include <iostream>
#include <bitset>
#include <string>

typedef union
{
    double f;
    unsigned long long u;
    int long long i;
} r;
 
int main() 
{
    r var1, var2;

    var1.f = -2.5 ;

    std::cout << var1.u << std::endl ;

    // empty constructor
    std::bitset<sizeof(double)*8> b1( var1.u ) ;
    std::bitset<sizeof(double)*8> b2( 13835058055282163712ull ) ;
 
    std::cout << b1 << std::endl ;
    std::cout << b2 << std::endl ;
    
 
    return 0;
}