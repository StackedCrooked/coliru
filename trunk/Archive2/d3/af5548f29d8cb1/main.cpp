#include <iostream>

    template <int A, int B>
    struct get_power
    {
        static const int value = A * get_power<A, B - 1>::value;
    };
    template <int A>
    struct get_power<A, 0>
    {
        static const int value = 1;
    };

int main()
{
    std::cout << get_power<3, 3>::value << std::endl;
}
