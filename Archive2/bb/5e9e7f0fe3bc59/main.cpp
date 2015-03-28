#include <iostream>
#include <iterator>
#include <cassert>
#include <vector>
#include <algorithm>
#include <boost/range/algorithm.hpp>
#include <boost/range/adaptors.hpp>

template<class InputIt2>
struct mixin
{
    mutable int delta = 0;
    mutable InputIt2 first2;
    InputIt2 last2;
    
    template<class T>
    auto operator()(T rank) const
    {
        while (first2 != last2 && *first2 <= rank + delta) { ++first2; ++delta; }
        return rank + delta;
    }
};

template<class InputIt2>
struct mixout
{
    mutable int delta = 0;
    mutable InputIt2 first2;
    InputIt2 last2;
    
    template<class T>
    auto operator()(T rank) const
    {
        while (first2 != last2 && *first2 < rank) { ++first2; ++delta; }
        return rank - delta;
    }
};

int main()
{
    auto set = std::vector<int>{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    auto pattern = std::vector<int>{ 8, 11, 12, 15 };
    using It = decltype(begin(pattern));

    auto result1 = set | boost::adaptors::transformed(mixin<It>{0, begin(pattern), end(pattern)});
    boost::copy(result1, std::ostream_iterator<int>(std::cout, ",")); std::cout << "\n";

    auto result2 = result1 | boost::adaptors::transformed(mixout<It>{0, begin(pattern), end(pattern)});
    boost::copy(result2, std::ostream_iterator<int>(std::cout, ",")); std::cout << "\n";
}
