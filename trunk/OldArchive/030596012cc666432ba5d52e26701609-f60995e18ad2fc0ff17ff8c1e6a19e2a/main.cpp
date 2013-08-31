#include <cstdio>
#include <cstddef>

constexpr bool f(const char* x) {
    return __builtin_constant_p(x);
}

int main()
{
    printf("%d\n", f(""));
    char x[10] = {};
    scanf("%s", x);
    printf("%d\n", f(x));
    return 0;
}