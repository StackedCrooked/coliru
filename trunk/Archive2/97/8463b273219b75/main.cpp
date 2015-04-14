#include <stdlib.h>

int main () {
    void* p;
    p = malloc(20);
    double* p2 = (double*)((char*)p + sizeof(double));
    *p2 = 5.;
    
    free(p);
}
