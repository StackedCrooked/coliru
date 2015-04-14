#include <stdlib.h>

int main () {
    void* p;
    p = malloc(20);
    double* p2 = (double*)((char*)p + 2);
    *p2 = 5.;
    
    free(p);
}
