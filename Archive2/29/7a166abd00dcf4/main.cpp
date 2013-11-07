#include <algorithm>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>
#include <limits>

using namespace std;

template<typename I, typename O>
I remove_duplicates(I first, I last, O out)
{
    using T = typename iterator_traits<I>::value_type;
    using limits = numeric_limits<T>;
    using Vector = vector<bool>; // or std::unordered_map for large T
    using Size = Vector::size_type;

    constexpr auto min = limits::lowest();
    constexpr auto max = limits::max();

    Vector had_before(Size(max - min) + 1, false);

    while(first != last)
    {
        T x = *first;
        auto &&was = had_before[Size(x - min)];
        if(!was)
        {
            was = true;
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
