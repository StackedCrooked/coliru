#include <iostream>

template <typename T> void foo(T first, int second)
{
    std::cout << "int: " << first << " " << second << " " << std::endl;
}

template <typename T> void foo(T first, double second)
{
    std::cout << "double: " << first << " " << second << " " << std::endl;
}

int main()
{
    foo('a', 0);
    foo('a', 0.0);
}
