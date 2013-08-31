#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <tuple>
#include <vector>

template<typename T, template <typename S, typename Alloc> class Collection, typename TAlloc>
std::tuple<T, T, T> properties(const Collection<T, TAlloc>& coll) 
{
     // Get min, max and sum of elements in a collection
     T minValue = std::numeric_limits<T>::max();
     T maxValue = std::numeric_limits<T>::min();
     T sum(0);
     for (auto && v : coll)
     {
         minValue = std::min<T>(minValue, v);
         maxValue = std::max<T>(maxValue, v);
         sum += v;
     }
     return std::make_tuple(minValue, maxValue, sum);
}

int main()
{
     std::vector<double> myVec(8);
     std::iota(begin(myVec), end(myVec), -4);
     auto result = properties(myVec);
     double min, max, sum;
     std::tie(min, max, sum) = result;
     std::cout << min << ", " << max << ", " << sum << std::endl;
}

