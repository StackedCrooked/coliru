// Array literal to Array Int

#include <cstring> // <string.h>
#include <iostream>
#include <cstdlib> // <stdlib.h>
#include <iomanip> // std::setw

const int SZ = 11 ;

const char* D[SZ] = //char *D[11] = // **** must be const
{
    "210743AAAEC8E34B",
    "7D16AE8F0E67A37E",
    "3A3B504AE96F6147",
    "A58ADFCA8EB3A217",
    "649821C088CD195A",
    "DBDBB68209898D44",
    "EC1FBB44455CD8D0",
    "D2545542803C5F82",
    "095720F6301B3065",
    "7A4D0B2607D72E55",
    "A29B364DF6469A48"
};

long long F[SZ] = {} ; //long long int F[11];

//char str_1[16];

int main() //main( )
{
    std::cout << "std::strtoll\n------------\n" ;
    for( int i = 0 ; i < SZ ; ++i )
    {
        F[i] = std::strtoll( D[i], nullptr, 16 ) ;

        std::cout << std::setw(2) << i << ". hex: 0x" << D[i] << "   dec:" ;

        if( errno == ERANGE ) { std::cout << "  * range error *\n" ; errno = 0 ; }
        else std::cout << std::setw(21) << F[i] << '\n' ;
    }

    std::cout << "\n\nstd::strtoull\n-------------\n" ;
    for( int i = 0 ; i < SZ ; ++i )
    {
        F[i] = std::strtoull( D[i], nullptr, 16 ) ;

        std::cout << std::setw(2) << i << ". hex: 0x" << D[i] << "   dec:" ;

        if( errno == ERANGE ) { std::cout << "  * range error *\n" ; errno = 0 ; }
        else std::cout << std::setw(21) << F[i] << '\n' ;
    }
}
