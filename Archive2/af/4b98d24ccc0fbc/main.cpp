#include <iostream>
#include <cstddef>


template<std::size_t V>
struct sum
{
    static constexpr std::size_t value=sum<V-1>::value+V;
};

template<>
struct sum<0>
{
    static constexpr std::size_t value=0;
};


int main() {
    std::cout << sum<300>::value << std::endl;
}