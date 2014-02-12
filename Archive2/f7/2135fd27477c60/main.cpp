#include <cstdlib>

struct alignas(8) big
{
   int array [1000];
};

big foo( const big& b )
{
    big rv = b ; 
    rv.array[0] = std::rand() ;
    return rv ;
}
