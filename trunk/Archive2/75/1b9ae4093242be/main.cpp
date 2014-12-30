#include <cstddef>
#include <iostream>

#define CONSTEXPR static constexpr
using namespace std;

template<size_t ... Sizes>
struct _size_check_impl
{
    static_assert(false, "Dimension has to be at least 1");
    CONSTEXPR size_t dimension = sizeof...(Sizes);
};

template<size_t ... Sizes>
constexpr size_t check_sizes()
{
    return _size_check_impl<Sizes...>::dimension;
}

template<size_t ... Sizes>
struct Test
{
    static constexpr size_t Final = check_sizes<Sizes...>();
};

int main()
{
    Test<> a; // This shouldn't get through the static assert
    Test<1, 2> b; // Passing
    Test<2> c; // Passing
    //cout << Test<>::Final; // With this it works just fine, bc Final is accessed
    return 0;
}