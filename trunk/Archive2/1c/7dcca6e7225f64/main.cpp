typedef struct A {
    int x;
    int y;
} A;

typedef struct B {
    A a;
    int d;
} B;

extern void ModifyX(A *a, B *b)
{
    b->a.x = a->x + 1;

    if(b->a.x != a->x)
    {
        b->a.x--;
    }
}

extern A* GetSuper(B *b)
{
    return (A *)(b);
}