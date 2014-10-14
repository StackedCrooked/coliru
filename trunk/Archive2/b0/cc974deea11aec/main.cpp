#include <iostream>
#include <cstddef>

template<typename I, typename P>
constexpr I partition_point(I first, I last, P p)
{
    while(first != last)
    {
        I middle = first + (last - first)/2;
        if( p(*middle) )
            last  = middle;
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
                   last  = first + c_str_length(first);

    struct P{ constexpr bool operator()(char x) const { return x >= 'f'; } };

    constexpr auto it = partition_point(first, last, P{});
    static_assert(*it == 'f', "");
    static_assert(it - first == 5, "");
}
