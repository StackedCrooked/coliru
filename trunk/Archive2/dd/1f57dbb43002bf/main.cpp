#include <iostream>

auto func()
{
    struct Test
    {
        int f();
    };
    return Test{};
}

int main()
{
    auto t = func();
    std::cout << t.f() << std::endl;
}

using func_Test = decltype(func());
int func_Test::f()
{
    return 7;
}
