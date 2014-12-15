#include <algorithm>
#include <functional>
#include <iostream>

#include <boost/algorithm/string/predicate.hpp>

int main()
{
    auto l = {1,2,3,4};
    auto l1 = {2};
    auto l2 = {5};
    std::cout << boost::algorithm::contains(l, l1) << std::endl;
    std::cout << boost::algorithm::contains(l, l2) << std::endl;
    
    using std::placeholders::_1;
    std::cout << std::any_of(l.begin(), l.end(), std::bind(std::equal_to<>(), 2, _1)) << std::endl;
    std::cout << std::any_of(l.begin(), l.end(), [](int i){ return i == 5; }) << std::endl;
}
