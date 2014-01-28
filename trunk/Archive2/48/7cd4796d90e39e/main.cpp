#include <iostream>
#include <utility>

struct bar
{
    bar() = default;
    bar(bar const&) { std::cout << "copy\n"; }
    bar(bar&&) { std::cout << "move\n"; }
};

template<class T>
void foo(T&& t)
{
    [&t](){ bar b(std::forward<T>(t)); (void)b; }();
}

int main()
{
    bar b;
    foo(b);
    foo(bar{});
}