#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/iterator/filter_iterator.hpp>

int main()
{
    auto const n = 2;
    auto const pred = [](int i){ return i > 0; };
    auto const v = std::vector<int>{ 0, 0 };

    auto const vb = boost::make_filter_iterator(pred, v.begin(), v.end());
    auto const ve = boost::make_filter_iterator(pred, v.end(), v.end());
    
    auto const nth_match = [&]() mutable->decltype(vb)
    {
        auto it = vb;
        auto count = 0;
        while (it != ve && count < n)
        {
            ++it;
            ++count;
        }
        return it;
    }();
    if (nth_match == ve)
        std::cout << "end\n";
    else
        std::cout << *nth_match << '\n';
}