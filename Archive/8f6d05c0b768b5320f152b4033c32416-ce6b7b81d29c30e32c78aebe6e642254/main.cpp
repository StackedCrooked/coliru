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
     std::tuple<double, double, double> result = properties<double, std::vector> (myVec);
     std::cout << std::get<reduction::min>(result) << ", " << std::get<reduction::max>(result) << ", " << std::get<reduction::sum>(result) << std::endl;

     int val = 2;
     std::list<int> myList(10, val); myList.push_back(100); myList.push_front(-100); 
     std::tuple<int, int, int> result2 = properties<int, std::list> (myList);
     std::cout << std::get<reduction::min>(result2) << ", " << std::get<reduction::max>(result2) << ", " << std::get<reduction::sum>(result2) << std::endl;

     // Boost ublas vectors
     ublas::vector<double, ublas::unbounded_array<double> > v2(10, 3.14159);
     std::tuple<double, double, double> result3 = properties<double, ublas::vector> (v2);
     std::cout << std::get<reduction::min>(result3) << ", " << std::get<reduction::max>(result3) << ", " << std::get<reduction::sum>(result3) << std::endl;

     ublas::vector<double, ublas::bounded_array<double, 20> > v3(10, 3.14159);
     std::tuple<double, double, double> result4 = properties<double, ublas::vector> (v3);
     std::cout << std::get<reduction::min>(result4) << ", " << std::get<reduction::max>(result4) << ", " << std::get<reduction::sum>(result4) << std::endl;

     return 0;
}

