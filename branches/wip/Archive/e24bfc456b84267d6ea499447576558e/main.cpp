#include <wheels/tuple.h++>
#include <cstdlib>
#include <tuple>
#include <iostream>


int main()
{
    return system(
        "find /usr/local/include/wheels -type f | grep -v detail | xargs cat; "
    );
}