#include <cstdlib>

struct big{
   int array [42000];
};

big foo() 
{
    return big{ { std::rand() } } ;
}
