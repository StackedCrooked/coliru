#include <algorithm>
#include <boost/iterator/counting_iterator.hpp>
#include <set>
#include <iostream>

int main()
{
    auto algo = [](const std::set<int>& s) -> int
    {
        auto it = std::mismatch(
           begin(s), end(s),
           boost::counting_iterator<int>(*begin(s))
        );
        return *it.second;
    };
 
    std::set<int> s1 {0,1,2,4};
    std::cout << algo(s1) << '\n';
    std::set<int> s2 {0,1,2,3};
    std::cout << algo(s2) << '\n';
    std::set<int> s3;
    std::cout << algo(s3) << '\n';
}