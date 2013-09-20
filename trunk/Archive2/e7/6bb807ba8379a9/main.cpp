#include <cstdio>
#include <functional>

struct foo
{
    std::function<void(void)> func;
};

int main(int, char**)
{
    auto inAuto = []()
    {
        puts("I am stored in auto.");
    };

    foo object;
    object.func = [] // you can omit the '()' if no arguments are specified
    {
        puts("I am stored in std::function<>.");
    };

    inAuto();
    object.func();

    return 0;
}
