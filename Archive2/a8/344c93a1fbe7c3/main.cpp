#include <iostream>

template<unsigned n>
struct intlog
{
    static const constexpr unsigned value = 1+intlog<n/2>::value;
};
template<>
struct intlog<0>
{
    static const constexpr unsigned value = 0;
};
template<>
struct intlog<1>
{
    static const constexpr unsigned value = 0;
};

int main()
{
    std::cout << "log2(10) = " << intlog<1023>::value << ".\n";
    std::cout << "log2(10) = " << intlog<1024>::value << ".\n";
    std::cout << "log2(10) = " << intlog<1025>::value << ".\n";
    std::cout << "log2(10) = " << intlog<4096>::value << ".\n";
}