#include <iostream>

template<typename I, typename T> 
constexpr I find(I first, T x)
{
    while(*first != x)
        ++first;
    return first;
}

int main()
{
    constexpr const char * x = "abc";
    static_assert(find(x, '\0') - x == 3, "");
}