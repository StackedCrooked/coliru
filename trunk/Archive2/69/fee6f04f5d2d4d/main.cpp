#include <iostream>

template <int ... values> struct sum;

template <int first, int ...rest>
struct sum<first, rest...>
{
    static constexpr int value = first + sum<rest...>::value;   
};

template <>
struct sum<>
{
    static constexpr int value = 0;   
};

int main() {
    std::cout << sum<1,2,3>::value << std::endl;
}
