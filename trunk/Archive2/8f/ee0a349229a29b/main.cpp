#include <cstddef>
#include <tuple>
#include <utility>

// index_sequence implementation (not available in C++11):
template <std::size_t... Is>
struct index_sequence {};

template <std::size_t N, std::size_t... Is>
struct make_index_sequence_h : make_index_sequence_h<N - 1, N - 1, Is...> {};

template <std::size_t... Is>
struct make_index_sequence_h<0, Is...>
{
    using type = index_sequence<Is...>;
};

template <std::size_t N>
using make_index_sequence = typename make_index_sequence_h<N>::type;

template <template <typename...> class T, std::size_t N, typename... Ts>
struct template_with_params_impl;

template <template <typename...> class T, std::size_t N, std::size_t... Is, std::size_t... Js, typename... Ts>
struct template_with_params_impl<T, N, index_sequence<Is...>, index_sequence<Js...>, Ts...>
{
    using type = T<typename std::tuple_element<Is, std::tuple<Ts...>>::type..., decltype(void(Js))...>;
};

template <template <typename...> class T, std::size_t N, typename... Ts>
using template_with_params = template_with_params_impl<T, N, make_index_sequence<N>, make_index_sequence<sizeof...(Ts) - N>, Ts...>;

// Tests:
#include <type_traits>

template <typename... Ts>
struct B {};

int main()
{
    template_with_params<B, 3, int>::type{};
    static_assert(std::is_same< template_with_params<B, 1, int, float, char>::type, 
                                B<int, void, void>  >{}, "!");
                                
    static_assert(std::is_same< template_with_params<B, 3, int, float, char, double>::type,
                               B<int, float, char, void>  >{}, "!");
}
