#include <boost/integer.hpp>
#include <limits>

namespace helpers
{
    // wrappers around Boost Integer http://www.boost.org/doc/libs/1_54_0/libs/integer/doc/html/boost_integer/integer.html#boost_integer.integer.sized
    template <bool is_signed, int bin_digits> struct select_twice;

    template <int bin_digits> struct select_twice<true, bin_digits> {
        using type = typename boost::int_t<bin_digits + 1>::least;
    };

    template <int bin_digits> struct select_twice<false, bin_digits> {
        using type = typename boost::uint_t<bin_digits>::least;
    };

}

template <typename Int>
    using select_twice = helpers::select_twice<std::numeric_limits<Int>::is_signed, std::numeric_limits<Int>::digits*2>;

template <typename Int>
    using twice_t = typename select_twice<Int>::type;

int main()
{
    static_assert(std::is_same<uint16_t, twice_t<uint8_t>>::value, "oops");
    static_assert(std::is_same<uint32_t, twice_t<uint16_t>>::value, "oops");
    static_assert(std::is_same<uint64_t, twice_t<uint32_t>>::value, "oops");
}
