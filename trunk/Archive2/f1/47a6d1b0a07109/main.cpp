#include <tuple>
#include <iostream>

std::tuple<int, int, bool> foo()
{
    return std::make_tuple(42, 1337, true);
}

int main()
{
    int a = 0, b = 0; bool c = false;
    std::forward_as_tuple(a, std::ignore, c) = foo();
    std::cout << b;
}