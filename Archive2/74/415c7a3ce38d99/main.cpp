#include <iostream>

template<typename F, typename ...Args>
auto apply(F f, Args... args)
{
    return f(args...);
}

double foo(int x, double y)
{
    return x + y;
}


int main()
{
    std::cout << apply(foo, 1, 0.1);
}