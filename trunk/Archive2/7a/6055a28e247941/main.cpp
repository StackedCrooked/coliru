#include <iostream>

namespace M 
{
    namespace N 
    {
        extern int j;
    }
    int i = 2;
}

int i = 4;
int M::N::j = i;

int main()
{
    std::cout << M::N::j << std::endl;
}
