#include <stdlib.h>

int get_initial_id(
    int
#ifdef NDEBUG
    n
#endif
)
{
#ifdef NDEBUG
    return rand() % n;
#else
    return 1000;
#endif
}
