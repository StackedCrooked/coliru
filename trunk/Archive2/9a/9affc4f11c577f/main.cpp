#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <set>

#include <cstdlib>

struct R;

using V = std::deque< R >;

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