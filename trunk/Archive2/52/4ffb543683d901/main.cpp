#include <iostream>
#include <numeric>

template<typename T>
T sum(std::initializer_list<T> vals)
{
    return std::accumulate(vals.begin(), vals.end(), T{});
}

int main()
{
    std::cout << sum({1, 2, 3, 4}) << std::endl;
}
