#include <functional>
#include <cstdio>

int main()
{

    int a = 9, b = 3;
    std::function<int(int)> f = [a](int b){ return a + b; };
    printf("%d + %d = %d\n", a, b, f(b));
    a = 1;
    printf("%d + %d = %d\n", a, b, f(b));
    return 0;
}
