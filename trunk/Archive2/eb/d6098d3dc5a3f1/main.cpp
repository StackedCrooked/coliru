#include <string>
#include <iostream>

template<typename T>
T fun(T x, T y)
{
    std::cout << __PRETTY_FUNCTION__ << '\n';
    return x + y;
}

template<int Func(int, int)>
struct foo
{
    int bar() { return Func(10, 20); }
};

int main()
{
    foo<fun> f;
    std::cout << f.bar() << '\n';
}
