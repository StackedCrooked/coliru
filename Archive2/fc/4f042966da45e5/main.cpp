#include <tuple>
#include <iostream>

template<typename ...ARGS1, typename ...ARGS2>
void foo(void (*)(ARGS1..., ARGS2...))
{
    std::cout << __PRETTY_FUNCTION__ << "\n";
}

void bar(int, bool, double, void*, float)
{
}

int main()
{
    foo(&bar);
    return 0;
}