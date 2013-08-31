#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/iterator/filter_iterator.hpp>

template<class ForwardIt, class Size, class Predicate>
ForwardIt find_if_nth(ForwardIt first, ForwardIt last, Size n, Predicate pred)
{
    auto vb = boost::make_filter_iterator(pred, first, last);
    auto const ve = boost::make_filter_iterator(pred, last, last);
    for (auto i = 0; i < n - 1 && vb != ve; ++i, ++vb) {}
    return vb.base();
}

int main()
{
    auto const v = std::vector<int>{ 0, 0, 3, 0, 2, 4, 5, 0, 7 };
    auto const n = 2;
    auto const pred = [](int i){ return i > 0; };
    auto const nth_match = find_if_nth(v.begin(), v.end(), n, pred);

    if (nth_match != v.end())
        std::cout << *nth_match << '\n';
    else
        std::cout << "less than n elements in v matched predicate\n";
}