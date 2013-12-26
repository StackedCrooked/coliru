#include <stdio.h>
#include <functional>

void foo(int a, int b)
{
    printf("%d %d\n", a, b);
}

typedef std::function<void (int, int)> IntIntToVoid;
typedef std::function<void (int)> IntToVoid;
typedef std::function<void ()> VoidToVoid;

IntToVoid curry(IntIntToVoid f, int n) {
    return [f, n](int m){ f(m, n); };
}

VoidToVoid curry(IntToVoid g, int m) {
    return [g, m](){ g(m); };
}

int main()
{
    IntToVoid f2 = curry(foo, 20);
    VoidToVoid f4 = curry(f2, 10);
    f4();
}
