#include <cstdlib>

struct alignas(16) big
{
   int array [42*4];
};

big foo() 
{
    return big{ { std::rand() } } ;
}
