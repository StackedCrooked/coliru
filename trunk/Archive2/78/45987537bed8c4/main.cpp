#define BOOST_RESULT_OF_USE_DECLTYPE // enable lambda arguments for Boost.Range
#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/adaptor/transformed.hpp>

#include <iostream>

struct OnlyEven
{
    typedef int argument_type;
    typedef std::pair<bool, int> result_type;
    result_type operator()(argument_type x) const
    {
        std::cout << "fun: " << x << std::endl;
        return std::make_pair(x % 2 == 0, x);
    }
} only_even;

int main()
{
    auto map = boost::adaptors::transformed;
    auto filter = boost::adaptors::filtered;
    int v[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto s = v | map(only_even) | filter([](const std::pair<bool, int> &x)->bool{ return x.first; });
    ++++++++++boost::begin(s);
    //for (auto &&i : s) {}
    return 0;
}