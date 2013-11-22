#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/rolling_count.hpp>
#include <boost/accumulators/statistics/rolling_sum.hpp>

namespace boost { namespace accumulators { namespace impl {
    template<typename Sample>
    struct rolling_count_non_zero : accumulator_base
    {
        typedef std::size_t result_type;
        rolling_count_non_zero(dont_care) : cnt_() {}
        template<typename Args>
        void operator ()(Args const &args)
        {
            if(args[sample] != 0)
                ++cnt_;
            if(is_rolling_window_plus1_full(args) && rolling_window_plus1(args).front() != 0 )
                --cnt_;
        }
        template<typename Args>
        result_type result(Args const &args) const { return cnt_; }
    private:
        std::size_t cnt_;
    };
} namespace tag {
    struct rolling_count_non_zero : depends_on< rolling_window_plus1 >
    {
        typedef accumulators::impl::rolling_count_non_zero< mpl::_1 > impl;
    };
} namespace extract {
    extractor<tag::rolling_count_non_zero> const rolling_count_non_zero = {};
}
using extract::rolling_count_non_zero;
}}

using namespace boost::accumulators;

template<typename Acc>
void demo_print(Acc& acc)
{
    std::cout << "cnt = " << rolling_count(acc) << ' '
              << "sum = " << rolling_sum(acc) << ' '
              << "nonzero cnt = " << rolling_count_non_zero(acc) << '\n';
}
int main()
{
    accumulator_set<double, features<tag::rolling_count_non_zero, tag::rolling_count, tag::rolling_sum> > acc(tag::rolling_window::window_size = 3);

    acc(1); demo_print(acc);
    acc(2); demo_print(acc);
    acc(3); demo_print(acc);
    acc(4); demo_print(acc);
    acc(0); demo_print(acc);
    acc(5); demo_print(acc);
}
