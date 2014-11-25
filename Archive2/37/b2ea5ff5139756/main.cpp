#include <stdio.h>

typedef struct T1 { int id; } T1;  
typedef struct T2 { int id; } T2;

void f(T1 *ptr) { printf("f called\n"); }

int main(void) 
{
    T2 obj; 
    T2 *ptr = &obj; 
    f(ptr); // shouldn't this be a compilation error ? 
    return 0;
}