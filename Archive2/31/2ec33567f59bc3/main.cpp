#include <cstdlib>

struct alignas(16) big
{
   int array [512];
};

big foo() 
{
    return big{ { std::rand() } } ;
}
