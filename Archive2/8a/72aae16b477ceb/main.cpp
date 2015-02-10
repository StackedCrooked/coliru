#include <iostream>

template <typename T>
auto id(T&& x) -> decltype(std::forward<T>(x))
{
    return std::forward<T>(x);
}

int main()
{
    int i = 0;
    const int j = 1;
    std::cout << id(i) << std::endl;
    std::cout << id(j) << std::endl;
    std::cout << id(2) << std::endl;
}