#include <cstdio>

struct foo
{
    foo()
    {
        puts("default constructing foo");
    }

    explicit foo(int)
    {
        puts("constructing foo from int");
    }

    foo(const foo&)
    {
        puts("copy-constructing foo");
    }

    foo& operator=(const foo&)
    {
        puts("copying foo");
        return *this;
    }

    int i;
};

void createFoo(foo& out)
{
    puts(__FUNCTION__);
    out = foo(1);
}

int main(int, char**)
{
    foo a;
    createFoo(a);
    foo b(a);
}
