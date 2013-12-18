#include <stdio.h>
#include <functional>

void foo(int a, int b)
{
    printf("%d %d\n", a, b);
}

void bar(void) {
    foo(10, 20);
}

std::function<void(int)> curry(std::function<void(int, int)> f, int n) {
    return std::function<void(int)> [int m]{ f(m, n); };
}

std::function<void()> curry(std::function<void(int)> g, int m) {
    return std::function<void()> []{ g(m); };
}

int main()
{
    bar();
    curry(curry(foo, 20), 10)();
}
