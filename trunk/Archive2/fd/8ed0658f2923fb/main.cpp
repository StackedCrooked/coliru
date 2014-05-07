#include <functional>
#include <cstdio>

void* operator new(std::size_t n)
{
    std::printf("operator new(%zu)\n", n);
    return std::malloc(n
    );
}


void foo(std::function<void()> f)
{
    f();
}


int main()
{
    long a = 1;
    long b = 2;
    long c = 3;
    long d = 4;
    printf("start of program\n");
    foo([]{ printf(" ^- for zero args\n"); });
    foo([a]{ printf(" ^- for 1 arg (%lu)\n", a); });
    foo([a, b]{ printf(" ^- for 2 args (%lu %lu)\n", a, b); });
    foo([a, b, c]{ printf(" ^- for 3 args (%lu %lu %lu)\n", a, b, c); });
    foo([a, b, c, d]{ printf(" ^- for 4 args (%lu %lu %lu %lu)\n", a, b, c, d); });
}
