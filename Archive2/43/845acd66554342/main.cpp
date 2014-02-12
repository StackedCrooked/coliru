#include <cstdlib>

struct big
{
   int array [42];
};

big foo( const big& b )
{
    big rv = b ; 
    rv.array[0] = std::rand() ;
    return rv ;
}
