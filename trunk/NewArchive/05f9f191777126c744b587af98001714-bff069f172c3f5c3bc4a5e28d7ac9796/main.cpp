#include <boost/mpl/vector.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/max_element.hpp>
#include <boost/integer.hpp>
#include <limits>

using namespace boost;

namespace best_fit_
{
    // wrappers around Boost Integer http://www.boost.org/doc/libs/1_54_0/libs/integer/doc/html/boost_integer/integer.html#boost_integer.integer.sized
    template <bool is_signed, int bin_digits> struct select_int;

    template <int bin_digits> struct select_int<true, bin_digits> {
        using type = typename boost::int_t<bin_digits + 1>::least;
    };

    template <int bin_digits> struct select_int<false, bin_digits> {
        using type = typename boost::uint_t<bin_digits>::least;
    };

    // query helper
    struct digits {
        template <typename I> using apply = mpl::int_<std::numeric_limits<I>::digits>;
    };
}

template <typename... I>
struct best_common_integral
{
    private:
        using Ints = mpl::vector<I...>;
        using Bits = typename mpl::transform<Ints, best_fit_::digits>::type;

        template <typename J>
            struct is_signed { static constexpr bool value = std::numeric_limits<J>::is_signed; };

        using max  = typename mpl::deref<typename mpl::max_element<Bits>::type>::type;

        // sigh, there is no `mpl::any`, AFAICT
        using sign = typename mpl::fold<
                    Ints, 
                    mpl::bool_<false>, 
                    mpl::if_<is_signed<mpl::_2>, mpl::bool_<true>, mpl::_1>
                >::type;
    public:
        using type = typename best_fit_::select_int<sign::value, max::value>::type;
};

#include <typeinfo>
#include <iostream>
#include <cassert>

int main()
{
    using case1 = best_common_integral<long, unsigned long, float, double, int>;
    using case2 = best_common_integral<unsigned int, unsigned long>;
    using case3 = best_common_integral<signed int, signed long>;
    using case4 = best_common_integral<signed int, unsigned int>;
    using case5 = best_common_integral<signed int, unsigned long>;

    //assert(typeid(case1::type) == typeid(double));
    assert(typeid(case2::type) == typeid(unsigned long));
    assert(typeid(case3::type) == typeid(signed long));
    assert(typeid(case4::type) == typeid(signed long));
    //assert(typeid(case5::type) == typeid(int128_t (maybe)));
}
