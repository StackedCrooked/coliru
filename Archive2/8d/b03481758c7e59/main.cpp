#include <cstdint>
#include <iostream>
#include <utility>

template <std::uint64_t... Seq>
struct sum;

template <std::uint64_t Head, std::uint64_t... Tail>
struct sum<Head, Tail...> 
    : std::integral_constant<std::uint64_t, Head + sum<Tail...>::value> { };
    
template <>
struct sum<> 
    : std::integral_constant<std::uint64_t, 0> { };

template <typename T>
struct sum_sequence;

template <std::uint64_t... Seq>
struct sum_sequence<std::integer_sequence<std::uint64_t, Seq...>> 
    : std::integral_constant<std::uint64_t, sum<Seq...>::value> { };
    
int
main() {
    std::cout << sum_sequence<std::make_integer_sequence<std::uint64_t, 10>>::value << '\n';
}
