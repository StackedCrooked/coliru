#include <iostream>
#include <tuple>
#include <type_traits>

namespace detail {

    template<typename...>
    struct truncate;

    // this specialization does the majority of the work

    template<typename... Head, typename T, typename... Tail>
    struct truncate< std::tuple<Head...>, std::tuple<T, Tail...> > {
        typedef typename
        truncate< std::tuple<Head..., T>, std::tuple<Tail...> >::type type;
    };

    // this one stops the recursion when there's only
    // one element left in the source tuple

    template<typename... Head, typename T>
    struct truncate< std::tuple<Head...>, std::tuple<T> > {
        typedef std::tuple<Head...> type;
    };
}

template<typename...>
struct tuple_truncate;

template<typename... Args>
struct tuple_truncate<std::tuple<Args...>> {

    // initiate the recursion - we start with an empty tuple,
    // with the source tuple on the right

    typedef typename detail::truncate< std::tuple<>, std::tuple<Args...> >::type type;
};

int main()
{
    typedef typename tuple_truncate< std::tuple<bool, double, int> >::type X;

    // test
    std::cout << std::is_same<X, std::tuple<bool, double>>::value; // 1, yay
}