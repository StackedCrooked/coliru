#include <iostream>
#include <boost/range/iterator_range.hpp>

int main()
{
    auto v = std::vector<int>{1, 2, 3};
    
    auto r = boost::make_iterator_range(std::begin(v), std::end(v));
    
    for (auto i : r)
    {
        std::cout << i;
    }
}