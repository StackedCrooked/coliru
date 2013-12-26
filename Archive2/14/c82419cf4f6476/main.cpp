#include <stdio.h>
#include <functional>

void foo(int a, int b)
{
    printf("%d %d\n", a, b);
}

typedef std::function<void (int, int)> IntIntToVoid;
typedef std::function<void (int)> IntToVoid;
typedef std::function<void ()> VoidToVoid;

using namespace std::placeholders;

IntToVoid curry(IntIntToVoid f, int n) {
    return std::bind(f, n, _1);
}

VoidToVoid curry(IntToVoid g, int m) {
    return std::bind(g, m);
}

int main()
{
    IntToVoid f2 = curry(foo, 10);
    VoidToVoid f4 = curry(f2, 20);
    f4();
}
