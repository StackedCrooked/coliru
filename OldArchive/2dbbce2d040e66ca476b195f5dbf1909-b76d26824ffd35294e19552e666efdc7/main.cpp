#include <stdlib.h>

int get_initial_id(int n)
{
#ifdef NDEBUG
    return rand() % n;
#else
    return 1000;
#endif
}
