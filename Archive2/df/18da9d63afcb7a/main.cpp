#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <vector>
#include <boost/range/algorithm/partition.hpp>
 
int main()
{
    std::vector<int> v;
    for (int i = 0; i < 10; ++i) v.push_back(i);
 
    std::cout << "Original vector:\n    ";
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
 
    // Partition the vector
    auto div = 2;
    auto p = boost::partition(v, [div] (int i) { return i % div == 0; });
 
    std::cout << "\nPartitioned vector:\n    ";
    for (auto e : v) std::cout << e << " ";
    std::cout << "\nBefore partition:\n    ";
    for (auto it = begin(v); it != p; ++it) std::cout << *it << " ";
    std::cout << "\nAfter partition:\n    ";
    std::copy(p,         v.end(), std::ostream_iterator<int>(std::cout, " "));
}