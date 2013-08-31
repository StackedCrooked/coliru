#include <cstdio>
#include <cstddef>

constexpr bool f(int x) {
    return __builtin_constant_p(x);
}

int main()
{
    printf("%d\n", f(0));
    int x = 0;
    scanf("%d", &x);
    printf("%d\n", f(x));
    return 0;
}