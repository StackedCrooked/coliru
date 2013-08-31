#include <stdlib.h>

#ifdef NDEBUG
int get_initial_id(int n) {
    return rand() % n;
}
#else
int get_initial_id(int) {
    return 1000;
}
#endif
