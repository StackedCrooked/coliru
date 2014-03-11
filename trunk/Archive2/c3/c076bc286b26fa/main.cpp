#include <stdlib.h>
#include <stdio.h>

typedef struct A {
    int x;
    int y;
}A;

typedef struct B {
    A a;
    int d;
}B;

extern void ModifyX(A *a, B *b);
extern A* GetSuper(B *);

int main(void){
    B *b = calloc(1, sizeof(*b));
    const B compare = {{1,0}, 0};
    A *a = GetSuper(b);

    ModifyX(a, b);
//    ((A*)b)->x++;

    if(b->a.x == compare.a.x)
    {
        printf("Passed");
        return EXIT_SUCCESS;
    }
    else
    {
        printf("Failed");
        return EXIT_FAILURE;
    }
}