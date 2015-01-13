#include <iostream>
#include <vector>
#include <deque>

#include <cstdlib>

struct R;

using V = std::vector< R >;

struct R
{
    
    int i;
    V v;
    
};

int
main()
{
    R r;
    V v;
    return EXIT_SUCCESS;
}