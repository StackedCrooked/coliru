#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/iterator/filter_iterator.hpp>

int main()
{
    auto const n = 2;
    auto const pred = [](int i){ return i > 0; };
    auto const v = std::vector<int>{ 0, 0, 3, 0, 2, 4, 5, 0, 7 };

    auto const vb = boost::make_filter_iterator(pred, v.begin(), v.end());
    auto const nth_match = std::next(vb, n - 1);
    std::cout << *nth_match << '\n';
}