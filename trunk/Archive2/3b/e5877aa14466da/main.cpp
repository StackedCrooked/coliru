#include <cstdlib>

struct big{
   int array [42];
};

big* foo() 
{
    return new big{ { std::rand() } } ;
}
