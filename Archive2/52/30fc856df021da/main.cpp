#include <utility>
#include <string>
#include <tuple>
#include <iostream>
#include <type_traits>

template<class T>
T Check(int index)
{
    std::cout << __PRETTY_FUNCTION__ << ' ' << index << '\n';
    return {};
}

template<typename Tuple, int... I>
static Tuple CallCheck(std::integer_sequence<int, I...>)
{
    return std::make_tuple(Check<typename std::tuple_element<I, Tuple>::type>(I)...);
}

template<typename Tuple>
Tuple CheckTuple()
{
    return CallCheck<Tuple>(std::make_integer_sequence<int, std::tuple_size<Tuple>::value>());
}

int main()
{
    auto tup = CheckTuple<std::tuple<int, float, std::string>>();
    static_assert(std::is_same<decltype(tup), std::tuple<int, float, std::string>>(), "");
}
