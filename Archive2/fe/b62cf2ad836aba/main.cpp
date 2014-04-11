#include <vector>

#include <boost/range/irange.hpp>
#include <boost/range/adaptor/sliced.hpp>
#include <boost/range/adaptor/transformed.hpp>

namespace R = boost::adaptors;

template<typename Range>
using range_difference_t = typename boost::range_difference<Range>::type;

template<typename Range>
auto inits(Range& range)
{
    using diff_t = range_difference_t<Range>;
    return R::transform(
        boost::irange(static_cast<diff_t>(0), boost::distance(range) + static_cast<diff_t>(1)),
        [range = &range](diff_t i) { return R::slice(*range, static_cast<diff_t>(0), i); }
        );
}

int main()
{
    std::vector<int> v = { 4, 55, 666, 777, 8888 };
    for(auto&& init: inits(v)) {
        std::cout << "[ ";
        for(auto&& e: init) {
            std::cout << e << ", ";
        }
        std::cout << "]\n";
    }
}