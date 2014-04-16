#include <algorithm>    // upper_bound, rotate
#include <functional>   // less
#include <iostream>     // iostream
#include <iterator>     // begin, end, iterator_traits, next
#include <vector>       // vector

template<class FwdIt, class Compare = std::less<typename std::iterator_traits<FwdIt>::value_type>>
void insertion_sort(FwdIt first, FwdIt last, Compare cmp = Compare())
{
    for (auto it = first; it != last; ++it) {
        auto const insertion = std::upper_bound(first, it, *it, cmp);
        std::rotate(insertion, it, std::next(it));
    }
}

int main()
{
    auto v = std::vector<int> { 4, 3, 2, 1 };
    insertion_sort(begin(v), end(v)); // now 1, 2, 3, 4
    for (auto e : v)
        std::cout << e << " ";
}
