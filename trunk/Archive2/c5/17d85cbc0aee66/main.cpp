#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/distance.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/less_equal.hpp>
#include <boost/mpl/max_element.hpp>
#include <boost/mpl/min_element.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/vector_c.hpp>
#include <iostream>

using namespace boost::mpl;

template<class Sequence, class Predicate = less<_1,_2>>
struct stable_min_element
: 
    // mpl::min_element uses max_element<Sequence, not_<Predicate>>
    max_element<Sequence, lambda<Predicate, _2, _1>>
{};

int main() 
{
    using V = vector_c<int, 1, 1, 1>;
    
    using MinIdx   = distance<begin<V>::type, min_element<V>::type>;
    using LEMinIdx = distance<begin<V>::type, min_element<V, less_equal<_1, _2> >::type>;
    using SMinIdx  = distance<begin<V>::type, stable_min_element<V>::type>;
    using MaxIdx   = distance<begin<V>::type, max_element<V>::type>;
    
    std::cout << MinIdx::value;     // ERROR: prints 2 instead of 0
    std::cout << LEMinIdx::value;   // 0
    std::cout << SMinIdx::value;    // 0
    std::cout << MaxIdx::value;     // 0
}
