#include <cstdio>
#include <cstring>

int func();

struct test
{
    int a;
    
    test() : a(7)
    {}
};

int x = func();

int func()
{
    static test obj;
    return ++obj.a;
}

int y = func();


int main()
{
    printf("%d %d\n", x, y);
}

