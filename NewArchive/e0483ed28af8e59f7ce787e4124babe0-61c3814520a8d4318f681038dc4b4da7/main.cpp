#include <iostream>

template<typename T>
void foo()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int main()
{
    auto it = "idk the type";
    foo<decltype(it)>();
}