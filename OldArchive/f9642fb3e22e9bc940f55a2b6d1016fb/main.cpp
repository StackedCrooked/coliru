#include <iostream>
#include <type_traits>


struct Int
{
    int a = 0;
};

static_assert(std::is_pod<Int>::value, "");


int main()
{
    Int n;
}