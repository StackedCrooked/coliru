#include <stdio.h>


template<int N>
struct A
{
    A<N-1> operator->()
    {
        printf("%d ", N);
        return A<N-1>();
    }
};


template<>
struct A<0>
{
    struct Boo { void boo() { puts("..boo!"); } };
    Boo* operator->() { return new Boo(); }
};


int main()
{
    A<10>()->boo();
}
