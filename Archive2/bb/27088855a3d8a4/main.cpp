#include <cstdlib>

struct big{
   int array [42];
};

big foo() 
{
    return big{ { std::rand() } } ;
}
