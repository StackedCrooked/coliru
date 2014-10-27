#include <iostream>
#include <string>
#include <vector>

struct A
{
    int a;
    char c[10];
};

struct B
{
    int a;
    int xxx;
    char c[20];
    float b;
};

void doflat(A & r)
{
    printf("nix");
}

void doflat(B & r)
{
    printf("%f   ", r.b);
}

template<typename T>
struct S;

template<>
struct S<A>
{
static void dotrace()
{ printf("do trace A"); }
};

template<>
struct S<B>
{
static void dotrace()
{ printf("do trace B");}
};



template<typename T>
void f1(T * r)
{
    printf("%i %s    ", r->a, r->c);
    doflat(*r);
    S<T>::dotrace();
}

int main()
{
    A aa = {1, "balb"};
    B bb = {2, 5, "bblb", 5.5 };
    
    f1(&aa);
    f1(&bb);
    
    return 1;
}
