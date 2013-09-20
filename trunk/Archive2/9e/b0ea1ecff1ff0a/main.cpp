#include <cstdio>

void foo(int)
{
    puts("int");
}

void foo(char*)
{
    puts("char*");
}

int main(int, char**)
{
    foo(1);
    foo(NULL);
    foo(nullptr);
    return 0;
}
