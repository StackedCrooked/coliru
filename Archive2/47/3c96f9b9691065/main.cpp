#include <cstdio>

struct V
{
    void* dat;
    int x;
};

int main() {
    
    V* v = new V;
    v->dat = new int;
    
    printf("%p\n", v->dat);
    printf("%p\n", *((void**)v));
    
    return 0;
}
