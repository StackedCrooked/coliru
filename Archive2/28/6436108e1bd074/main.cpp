#include <functional>
using namespace std;

void foo(function<int(int, int)> x)
{
    volatile auto y = x(111, 222) + 555;
    (void)y;
}

void test_foo()
{
    foo([](int x, int y){ return x+y; });
}
/*********************************************/
template<typename F>
void bar(F x)
{
    volatile auto y = x(111, 222) + 555;
    (void)y;
}

void test_bar()
{
    bar([](int x, int y){ return x+y; });
}
