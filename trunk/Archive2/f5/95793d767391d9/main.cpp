#include <cstddef>
#include <cstdio>

struct test
{
    int a;
    alignas(16) int b;
};

int main()
{
    printf("%d", offsetof(test, b));
}