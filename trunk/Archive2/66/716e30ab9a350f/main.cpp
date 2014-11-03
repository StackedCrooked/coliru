#include <stdio.h>

namespace NAMESPACEFOO
{

struct MEANINGLESSTAG {};

template <typename TYPENAMEBAR>
MEANINGLESSTAG HELLO(TYPENAMEBAR bar)
{

    printf("hello, %d\n", bar);

    return MEANINGLESSTAG();

}
} // !namespace

int main(int ac, char ** av)
{
    NAMESPACEFOO::HELLO (ac);
}

