#include <cstdio>
#include <cstddef>

constexpr bool f(int x) {
    static_assert(__builtin_constant_p(x), "");
    return __builtin_constant_p(x);
}

int main()
{
    printf("%d\n", f(0));
    return 0;
}