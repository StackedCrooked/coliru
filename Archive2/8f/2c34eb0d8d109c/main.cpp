#include <iostream>

template <std::size_t N>
std::size_t fibonacci()
{
    return fibonacci<N - 1>() + fibonacci<N - 2>();
}

template <>
std::size_t fibonacci<0>()
{
    return 0;
}

template <>
std::size_t fibonacci<1>()
{
    return 1;
}

int main()
{
    std::cout << fibonacci<7>() << std::endl;
}