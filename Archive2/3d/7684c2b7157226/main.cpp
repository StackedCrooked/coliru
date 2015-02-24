#include <functional>
using namespace std;

void foo(function<int(int, int)> x)
{
    volatile auto y = x(111, 222) + 555;
    (void)y;
}

void bar()
{
    foo([](int x, int y){ return x+y; });
}
