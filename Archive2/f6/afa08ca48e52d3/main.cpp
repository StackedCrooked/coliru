#include <algorithm>
#include <iostream>
#include <iterator>
#include <utility>
#include <cstddef>
#include <bitset>
#include <limits>

using namespace std;

template<typename I, typename O>
I remove_duplicates(I first, I last, O out)
{
    using T = typename iterator_traits<I>::value_type;
    using limits = numeric_limits<T>;

    constexpr auto min = limits::lowest();
    constexpr auto max = limits::max();

    bitset<size_t(max - min) + 1> had_before;

    while(first != last)
    {
        T x = *first;
        size_t i = x - min;
        if(!had_before[i])
        {
            had_before.set(i);
            *out = x;
            ++out;
        }
        ++first;
    }
    return out;
}

int main()
{
    char s[] = "Qqqqqqqwwwww111qq1q1Qa";
    auto first = begin(s), last = end(s);
    auto new_last = remove_duplicates(first, last, first);
    for_each(first, new_last, [](char x) { cout << x; });
}
