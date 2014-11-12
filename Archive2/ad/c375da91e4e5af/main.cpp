#include <cstdio>

template <typename T> void foo(T)
{
    std::puts("1");
}
template <typename T> void foo(T*)
{
    std::puts("2");
}
template <>           void foo<int>(int*)
{
    std::puts("3");
}

template <typename T> void bar(T)
{
    std::puts("4");
}
template <>           void bar<int*>(int*)
{
    std::puts("5");
}
template <typename T> void bar(T*)
{
    std::puts("6");
}

int main()
{
    foo(new int);
    bar(new int);
}
