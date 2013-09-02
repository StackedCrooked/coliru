#include <cstdio>

struct X {
    template<typename T>
    void foo(T);

    int i;
};

template<>
void X::foo<int>(int val)
{
    i = val;
}

int main()
{
    X x;
    x.foo(42);
    printf("%d", x.i);
}