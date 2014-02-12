#include <cstdlib>

struct alignas(8) big
{
   int array [42*16];
};

big foo( const big& b )
{
    big rv = b ; 
    return rv ;
}
