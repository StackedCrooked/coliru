#include <cstring>
#include <cstdlib>
#include <cstdio>

const int SZ = 11 ;

const char* D[SZ] = // ****** must be const char* ******
                    // ****** MUST BE const char* ******
                    // ****** must be const char* ******
                    // ****** MUST BE const char* ******
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

unsigned long long F[SZ] = {} ; //long long int F[11];

int main()
{
    for( int i = 0 ; i < SZ ; ++i )
    {
        F[i] = std::strtoull( D[i], nullptr, 16 ) ;
        std::printf( "%2d. %016llx\n", i, F[i] ) ;
    }
}
