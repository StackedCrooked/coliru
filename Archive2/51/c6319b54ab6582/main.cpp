#include <cstddef>

template <std::size_t Size>
struct Array
{
    constexpr static int const array[Size] = {};
};

template <std::size_t Size>
struct Test
{
    constexpr static int const array[Size] = Array<Size>::array;
};

int main(){}