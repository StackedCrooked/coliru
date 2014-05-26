#include <tuple>
#include <type_traits>

template<typename...Ts>
using tuple_cat_t = decltype(std::tuple_cat(std::declval<Ts>()...));

template<typename T, typename...Ts>
using remove_t = tuple_cat_t<
    typename std::conditional<
        std::is_same<T, Ts>::value,
        std::tuple<>,
        std::tuple<Ts>
    >::type...
>;

int main()
{
    static_assert(std::is_same<
        remove_t<int, int, char, int, float, int>,
        std::tuple<char, float>
    >::value, "Oops");
}
