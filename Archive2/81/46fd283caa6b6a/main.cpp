#include <new>

struct foo
{
};

struct bar
{
    int i;
};

int main()
{
    foo f;
    new (&f) bar{};
}
