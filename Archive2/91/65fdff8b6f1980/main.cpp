#include <type_traits>
#include <vector>

#include <boost/range/irange.hpp>
#include <boost/range/adaptor/sliced.hpp>
#include <boost/range/adaptor/transformed.hpp>

namespace R = boost::adaptors;

template<typename Range>
using range_difference_t = typename boost::range_difference<Range>::type;

namespace functors {

template<typename Range>
struct slice {
    using difference_type = range_difference_t<Range>;
    Range* range;

    explicit slice(Range& range)
        : range(&range)
    {}

    boost::sliced_range<Range> operator()(difference_type index) const
    {
        return R::slice(*range, static_cast<difference_type>(0), index);
    }
};

} // functors

template<typename Range>
using inits_type =
    boost::transformed_range<
        functors::slice<Range>,
        const boost::integer_range<range_difference_t<Range>>
    >;

// calling inits with rvalues is not supported on purpose
template<typename Range>
inits_type<Range> inits(Range& range)
{
    using diff_t = range_difference_t<Range>;
    return R::transform(
        // use boost::size instead of boost::distance to restrict
        // inits to working efficiently on random-access ranges only
        boost::irange(static_cast<diff_t>(0), boost::distance(range) + static_cast<diff_t>(1)),
        functors::slice<Range> { range }
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