#include <type_traits>
#include <limits>

template <typename T>
struct inferred_integer
{
    typedef T data_t;
};

template<
    typename Integer,
    typename std::enable_if_t<
        (  std::numeric_limits<Integer>::is_integer
        && std::is_convertible<
            Integer, inferred_integer<Integer>::data_t
        >::value )
    , int> = 0
>
inferred_integer<Integer> from_int(const Integer& i) {
    return inferred_integer<Integer>(i);
}