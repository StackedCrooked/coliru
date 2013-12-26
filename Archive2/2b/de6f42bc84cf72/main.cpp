#include <stdio.h>
#include <functional>

void foo(int a, int b)
{
    printf("%d %d\n", a, b);
}

int main()
{
    auto f1 = [](int b){ foo(10, b); };
    std::function<void (int)> f2 = f1; // fine
    auto f3 = [f2]{ return f2(20); };
    std::function<void ()> f4 = f3; // stack overflow
    f4();
}
