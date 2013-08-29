// TemplateTemplateNew.cpp
//
// Example of template template parameters; encapsulating
// higher-order STL algorithms.
//
// Use template-template parameter instead of traits and formal template 
// parameters. 
//
// Rationale: 'mechanisms' on top of STL.
//
// djd
//
//

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <list>
#include <numeric>
#include <tuple>
#include <vector>

#include <boost/numeric/ublas/vector.hpp>          // The vector class.
namespace ublas=boost::numeric::ublas;

namespace reduction
{
  enum reduction : std::size_t { min = 0, max = 1, sum = 2 };
}

//template<typename T, template <typename S, typename Alloc> class Collection, typename TAlloc = std::allocator<T> >
template<typename T, template <typename S, typename Alloc> class Collection, typename TAlloc>
     std::tuple<T, T, T> properties(const Collection<T, TAlloc>& coll) 
{
     // Get min, max and sum of elements in a collection
     auto minmax = std::minmax_element(coll.begin(), coll.end());
     T initVal(0);
     T sum = std::accumulate(coll.begin(), coll.end(), initVal);
     return std::make_tuple(*minmax.first, *minmax.second, sum);
}




int main()
{
 
     std::vector<double> myVec(10, 3.14159);
     auto result = properties(myVec);
     double min, max, sum;
     std::tie(min, max, sum) = result;
     std::cout << min << ", " << max << ", " << sum << std::endl;

     return 0;
}

