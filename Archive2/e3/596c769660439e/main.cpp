#include <iostream>
#include <cstddef>

template<typename I, typename T>
constexpr I partition_point_m(I first, I last, T x)
{
    while(first != last)
    {
        I middle = first + (last - first)/2;
        if( *middle == x )
            last = middle;
        else
            first = middle + 1;
    }
    return first;
}

template<typename I, typename T>
constexpr I find(I first, T x)
{
    while(*first != x)
        ++first;
    return first;
}

constexpr std::size_t c_str_length(const char *x)
{
    return find(x, '\0') - x;
}

int main()
{
    using namespace std;
    constexpr auto first = "abcdefg",
                   last = first + c_str_length(first);
    constexpr auto it = partition_point_m(first, last, 'f');
    static_assert(*it == 'f', "");
    static_assert(it - first == 5, "");
}