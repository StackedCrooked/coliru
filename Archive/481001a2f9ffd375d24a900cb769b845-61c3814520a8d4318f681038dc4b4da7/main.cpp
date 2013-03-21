#include <iostream>

template<typename T>
void foo(T = T())
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int main()
{
    foo<decltype("idk the type")>();
    auto s = "idk the type";
    foo<decltype(s)>();
    foo(s);
}