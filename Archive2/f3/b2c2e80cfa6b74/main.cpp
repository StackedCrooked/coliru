#include <cstdio>
#include <utility>

struct foo
{
    explicit foo(int) // no implicit conversion is allowed
    {
        puts("constructing foo from int");
    }

    foo(const foo&)
    {
        puts("copy-constructing foo");
    }

    foo(const foo&&)
    {
        puts("move-constructing foo");
    }

    int i;
};

foo createFoo()
{
    return foo(1);
}

int main(int, char**)
{
    // you can use foo instead of auto if you prefer, of course
    auto a = createFoo();
    foo b(a);
    foo c(std::move(b));
}
