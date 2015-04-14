#include <stdlib.h>

struct A { int a;};

int main () {
    struct A a;
    void* p;
    struct A* p2;
    a.a = 1;
    p = malloc(2*sizeof(struct A));
    p2 = (char*)p + sizeof(struct A);
    *p2 = a;
    
    double* b = (double*)p2;
    *b = 0.;
    
    int c = p2->a;
    
    free(p);
}
