#include <algorithm>
#include <initializer_list>
#include <iostream>

unsigned product(std::initializer_list<unsigned> factors)
{
    auto result = 1;
    for(auto factor : factors) result *= factor;
    return result;
}

template<typename ...T> unsigned product(T ...t)
{
    return product( { t... });
}

int main()
{
    std::cout << product(2u) << std::endl;
    std::cout << product(2u, 3u) << std::endl;
    std::cout << product(2u, 3u, 5u) << std::endl;
    std::cout << product(2u, 3u, 5u, 7u) << std::endl;
}
