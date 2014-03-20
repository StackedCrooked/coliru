#include <cstddef>
#include <iostream>

template<std::size_t... Ints> struct index_sequence;

template<std::size_t N>
struct sum
{
    static constexpr std::size_t value=sum<N-1>::value+N;
};

template<>
struct sum<0>
{
    static constexpr std::size_t value=0;
};

int main() {
    
    std::cout << sum<500>::value << std::endl;
    
}