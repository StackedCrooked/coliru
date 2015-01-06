#include <tuple>
#include <iostream>

namespace detail
{
    template <typename F, typename TUPLE, std::size_t...Is>
    auto call(F f, const TUPLE& t, std::index_sequence<Is...>)
    -> decltype(f(std::get<Is>(t)...))
    {
        return f(std::get<Is>(t)...);
    }
}

template <typename F, typename TUPLE>
auto call(F f, const TUPLE& t)
-> decltype (detail::call(f, t,
        std::make_index_sequence<std::tuple_size<TUPLE>::value>()))
{
    return detail::call(f, t,
        std::make_index_sequence<std::tuple_size<TUPLE>::value>());
}

std::tuple <int,int> tuple_ints(int x,int y) {
    return std::tuple <int,int> (x,y);
}

int add(int x,int y) {
    return x+y;
}

int main() {
    std::cout << call(add, tuple_ints(1,2)) << std::endl;
}
